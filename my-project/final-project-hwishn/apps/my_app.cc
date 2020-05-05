// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include <cinder/app/App.h>
#include "cinder/gl/gl.h"
#include <jsoncpp/json.h>
#include <cinder/audio/Voice.h>
#include <algorithm>
#include <random>


namespace myapp {

using cinder::app::KeyEvent;

bool answeredQuestion = false;
Json::Value jsonData;
int index = 0;
std::string question;
std::string answer1;
std::string answer2;
std::string answer3;
std::string answer4;
std::string game_over_text = "your score is ";
int score;
auto rng = std::default_random_engine {};
std::vector<std::string> answered;
std::vector<std::string> correct;
bool finished = false;
bool current = true;
std::vector<std::string> answers;
cinder::audio::VoiceRef mVoice;

void getQuestions() {
    std::ifstream file("C:\\Users\\butte\\CLionProjects\\Cinder\\my-project\\final-project-hwishn\\assets\\game.json");
    Json::Reader reader;
    reader.parse(file, jsonData);
}

void setQuestions() {
    question = jsonData["results"][index].get("question", " ").asString();
    answer1 = jsonData["results"][index].get("correct_answer", " ").asString();
    answer2 = jsonData["results"][index].get("incorrect_answers", " ")[0].asString();
    answer3 = jsonData["results"][index].get("incorrect_answers", " ")[1].asString();
    answer4 = jsonData["results"][index].get("incorrect_answers", " ")[2].asString();
    correct.push_back(answer1);
    answers.clear();
    answers.push_back(answer1);
    answers.push_back(answer2);
    answers.push_back(answer3);
    answers.push_back(answer4);
    std::shuffle(std::begin(answers), std::end(answers), rng);
}

void MyApp::setup() {
    getQuestions();

    setQuestions();
    // Bind the Osc Receiver...
    try {
        mOscReceiver.bind();
    }
    catch( const ci::Exception &ex ) {
        CI_LOG_EXCEPTION( "OscReceiver bind", ex );
        quit();
    }


    // And listen for messages.
    mOscReceiver.listen(
            []( asio::error_code ec, asio::ip::udp::endpoint ep ) -> bool {
                if( ec ) {
                    CI_LOG_E( "Error on listener: " << ec.message() << " Error Value: " << ec.value() );
                    return false;
                }
                else
                    return true;
            } );

    cinder::audio::SourceFileRef sourceFile = cinder::audio::load(
            cinder::app::loadAsset( "Soft-lounge-background-track.mp3" ));
    mVoice = cinder::audio::Voice::create( sourceFile );
    mVoice->start();

}

    void MyApp::touchesBegan( TouchEvent event )
    {
        for( auto & touch : event.getTouches() ) {
            Color newColor( CM_HSV, Rand::randFloat(), 1, 1 );
            mActivePoints.insert( std::make_pair( touch.getId(), TouchPoint( touch.getPos(), newColor ) ) );
        }
    }

    void MyApp::touchesMoved( TouchEvent event )
    {
        for( auto & touch : event.getTouches() )
            mActivePoints[touch.getId()].addPoint( touch.getPos() );
    }

    void MyApp::touchesEnded( TouchEvent event )
    {
        for( auto & touch : event.getTouches() ) {
            mActivePoints[touch.getId()].startDying();
            mDyingPoints.push_back( mActivePoints[touch.getId()] );
            mActivePoints.erase( touch.getId() );
        }
    }

    void PrintText(const std::string& text, const cinder::Color& color,
                   const cinder::ivec2& size, const cinder::vec2& loc) {
        cinder::gl::color(color);

        auto box = TextBox()
                .alignment(TextBox::CENTER)
                .font(cinder::Font("Arial", 30))
                .size(size)
                .color(color)
                .backgroundColor(ColorA(0,0,0,0))
                .text(text);

        const auto box_size = box.getSize();
        const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
        const auto surface = box.render();
        const auto texture = cinder::gl::Texture::create(surface);
        cinder::gl::draw(texture, locp);
    }

void MyApp::draw() {
    if (finished) {
        cinder::gl::clear(Color(1, 1, 1));
        PrintText(game_over_text, color, size, getWindowCenter());
        PrintText(std::to_string(score), color, size, {getWindowCenter().x + 100,
                                                       getWindowCenter().y});
        PrintText("out of 10", color, size, {getWindowCenter().x + 200,
                                             getWindowCenter().y});
        current = false;
    } else if (current) {
        cinder::gl::clear(Color(1, 1, 1));
        PrintText(question, color, size, getWindowCenter());
        PrintText("a." + answers[0], color, size, {200, 120});
        PrintText("b." +answers[1], color, size, {600, 120});
        PrintText("c." + answers[2], color, size, {200, 680});
        PrintText("d." + answers[3], color, size, {600, 680});
    }

    //gl::color( Color( 1, 1, 0 ) );
    //std::vector<TouchEvent::Touch> activeTouches(getActiveTouches());
    //for( auto touchIt = activeTouches.begin(); touchIt != activeTouches.end(); ++touchIt ) {
        //gl::drawLine( touchIt->getPos(), touchIt->getPos());
    //}
}

void MyApp::setNextQuestion() {
    index++;

    if ( index < jsonData["results"].size()) {
        setQuestions();
        draw();
    } else {
        for (int i = 0; i < answered.size(); i++) {
            if (answered[i] == correct[i]) {
                score++;
            }
        }
        finished = true;
        draw();
    }
}

void MyApp::keyDown(KeyEvent event) {
    if( event.getChar() == 'a' ) {
        answered.push_back(answers[0]);
        setNextQuestion();
    } else if (event.getChar() == 'b') {
        answered.push_back(answers[1]);
        setNextQuestion();
    } else if (event.getChar() == 'c') {
        answered.push_back(answers[2]);
        setNextQuestion();
    } else if (event.getChar() == 'd') {
        answered.push_back(answers[3]);
        index++;
        setNextQuestion();
    }

}

void MyApp::update() {

}

MyApp::MyApp() :App(), mOscReceiver( tuio::Receiver::DEFAULT_TUIO_PORT ),
                 mTuio( app::getWindow(), &mOscReceiver )
{
}


}  // namespace myapp
