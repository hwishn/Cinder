// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include "cinder/app/RendererGl.h"
#include <C:\Users\butte\CLionProjects\Cinder\blocks\TUIO\src\cinder\tuio\Tuio.h>
#include "cinder/System.h"
#include "cinder/Rand.h"
#include "cinder/PolyLine.h"
#include "cinder/gl/gl.h"


namespace myapp {

using namespace ci;
using namespace ci::app;

class MyApp : public cinder::app::App {

    struct TouchPoint {
        TouchPoint() {}
        TouchPoint( const vec2 &initialPt, const Color &color )
                : mColor( color ), mTimeOfDeath( -1.0 )
        {
            mLine.push_back( initialPt );
        }

        void addPoint( const vec2 &pt ) { mLine.push_back( pt ); }

        void draw() const
        {
            if( mTimeOfDeath > 0 ) // are we dying? then fade out
                gl::color( ColorA( mColor, ( mTimeOfDeath - mCurrentTime ) / 2.0f ) );
            else
                gl::color( mColor );

            gl::draw( mLine );
        }

        void startDying() {mTimeOfDeath = mCurrentTime + 2.0f; } // two seconds til dead

         bool isDead()  { return mCurrentTime > mTimeOfDeath; }

        PolyLine2f	mLine;
        Color		mColor;
        float mTimeOfDeath;
        double mCurrentTime = myapp::getElapsedSeconds();
    };

public:
  MyApp();
    void	touchesBegan( TouchEvent event ) override;
    void	touchesMoved( TouchEvent event ) override;
    void	touchesEnded( TouchEvent event ) override;
    void	setup() override;
    void	draw() override;
    void	keyDown( KeyEvent event ) override;

    std::map<uint32_t, TouchPoint>	mActivePoints;
    std::list<TouchPoint>			mDyingPoints;
    osc::ReceiverUdp			mOscReceiver;
    tuio::Receiver				mTuio;
    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {700, 50};
    const Color color = Color::black();

    void update() override;
    void getQuestions();
    void setNextQuestion();
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
