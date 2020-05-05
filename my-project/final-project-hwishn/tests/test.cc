// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cinder/Rand.h>

#include <mylibrary/example.h>
#include <jsoncpp/json.h>

//testing json parsing
TEST_CASE("json is not null") {
    Json::Value jsonData;
    //exact code for getQuestions() that parses json
    std::ifstream file("C:\\Users\\butte\\CLionProjects\\Cinder\\my-project\\final-project-hwishn\\assets\\game.json");
    Json::Reader reader;
    reader.parse(file, jsonData);
    REQUIRE(jsonData != nullptr);
}

TEST_CASE("result array is correct size ") {
    Json::Value jsonData;
    //exact code for getQuestions() that parses json
    std::ifstream file("C:\\Users\\butte\\CLionProjects\\Cinder\\my-project\\final-project-hwishn\\assets\\game.json");
    Json::Reader reader;
    reader.parse(file, jsonData);
    REQUIRE(jsonData["results"].size() == 10);
}

TEST_CASE("first question text is correct") {
    Json::Value jsonData;
    //exact code for getQuestions() that parses json
    std::ifstream file("C:\\Users\\butte\\CLionProjects\\Cinder\\my-project\\final-project-hwishn\\assets\\game.json");
    Json::Reader reader;
    reader.parse(file, jsonData);
    REQUIRE(jsonData["results"][0].get("question", " ").asString()
            == "America's Strategic Defense System during the Cold War was nicknamed after this famous movie.");
}

TEST_CASE("correct answer text is correct") {
    Json::Value jsonData;
    //exact code for getQuestions() that parses json
    std::ifstream file("C:\\Users\\butte\\CLionProjects\\Cinder\\my-project\\final-project-hwishn\\assets\\game.json");
    Json::Reader reader;
    reader.parse(file, jsonData);
    REQUIRE(jsonData["results"][0].get("correct_answer", " ").asString()
            == "Star Wars");
}

TEST_CASE("first incorrect answer text is correct") {
    Json::Value jsonData;
    //exact code for getQuestions() that parses json
    std::ifstream file("C:\\Users\\butte\\CLionProjects\\Cinder\\my-project\\final-project-hwishn\\assets\\game.json");
    Json::Reader reader;
    reader.parse(file, jsonData);
    REQUIRE(jsonData["results"][0].get("inccorect_answers", " ")[0].asString()
            == "Jaws");
}

TEST_CASE("second inccorect answer is correct") {
    Json::Value jsonData;
    //exact code for getQuestions() that parses json
    std::ifstream file("C:\\Users\\butte\\CLionProjects\\Cinder\\my-project\\final-project-hwishn\\assets\\game.json");
    Json::Reader reader;
    reader.parse(file, jsonData);
    REQUIRE(jsonData["results"][0].get("inccorect_answers", " ")[1].asString()
            == "Blade Runner");
}

TEST_CASE("third inccorect answer is correct") {
    Json::Value jsonData;
    //exact code for getQuestions() that parses json
    std::ifstream file("C:\\Users\\butte\\CLionProjects\\Cinder\\my-project\\final-project-hwishn\\assets\\game.json");
    Json::Reader reader;
    reader.parse(file, jsonData);
    REQUIRE(jsonData["results"][0].get("inccorect_answers", " ")[2].asString()
            == "Alien");
}

TEST_CASE("last question text is correct") {
    Json::Value jsonData;
    //exact code for getQuestions() that parses json
    std::ifstream file("C:\\Users\\butte\\CLionProjects\\Cinder\\my-project\\final-project-hwishn\\assets\\game.json");
    Json::Reader reader;
    reader.parse(file, jsonData);
    REQUIRE(jsonData["results"][9].get("question", " ")[1].asString()
            == "Which actor was not a major character in TV Show Freaks and Geeks?");
}

TEST_CASE("response code is zero") {
    Json::Value jsonData;
    //exact code for getQuestions() that parses json
    std::ifstream file("C:\\Users\\butte\\CLionProjects\\Cinder\\my-project\\final-project-hwishn\\assets\\game.json");
    Json::Reader reader;
    reader.parse(file, jsonData);
    REQUIRE(jsonData["response_code"].asInt() == 0);
}

//testing answer shuffling
TEST_CASE("answers shuffle") {
    Json::Value jsonData;
    //exact code for getQuestions() that parses json
    std::ifstream file("C:\\Users\\butte\\CLionProjects\\Cinder\\my-project\\final-project-hwishn\\assets\\game.json");
    Json::Reader reader;
    reader.parse(file, jsonData);
    //code I used to shuffle the answers
    auto rng = std::default_random_engine {};
    std::vector<std::string> answers;
    std::string answer1 = jsonData["results"][0].get("correct_answer", " ").asString();
    std::string answer2 = jsonData["results"][0].get("incorrect_answers", " ")[0].asString();
    std::string answer3 = jsonData["results"][0].get("incorrect_answers", " ")[1].asString();
    std::string answer4 = jsonData["results"][0].get("incorrect_answers", " ")[2].asString();
    answers.clear();
    answers.push_back(answer1);
    answers.push_back(answer2);
    answers.push_back(answer3);
    answers.push_back(answer4);
    std::shuffle(std::begin(answers), std::end(answers), rng);
    REQUIRE((answers[0] != answer1 || answers[1] != answer2)
    || (answers[3] != answer3 || answers[4] != answer4));
}

TEST_CASE("different question shuffles") {
    Json::Value jsonData;
    //exact code for getQuestions() that parses json
    std::ifstream file("C:\\Users\\butte\\CLionProjects\\Cinder\\my-project\\final-project-hwishn\\assets\\game.json");
    Json::Reader reader;
    reader.parse(file, jsonData);
    //code I used to shuffle the answers
    auto rng = std::default_random_engine {};
    std::vector<std::string> answers;
    std::string answer1 = jsonData["results"][9].get("correct_answer", " ").asString();
    std::string answer2 = jsonData["results"][9].get("incorrect_answers", " ")[0].asString();
    std::string answer3 = jsonData["results"][9].get("incorrect_answers", " ")[1].asString();
    std::string answer4 = jsonData["results"][9].get("incorrect_answers", " ")[2].asString();
    answers.clear();
    answers.push_back(answer1);
    answers.push_back(answer2);
    answers.push_back(answer3);
    answers.push_back(answer4);
    std::shuffle(std::begin(answers), std::end(answers), rng);
    REQUIRE((answers[0] != answer1 || answers[1] != answer2)
            || (answers[3] != answer3 || answers[4] != answer4));
}

TEST_CASE("anouther question shuffles") {
    Json::Value jsonData;
    //exact code for getQuestions() that parses json
    std::ifstream file("C:\\Users\\butte\\CLionProjects\\Cinder\\my-project\\final-project-hwishn\\assets\\game.json");
    Json::Reader reader;
    reader.parse(file, jsonData);
    //code I used to shuffle the answers
    auto rng = std::default_random_engine {};
    std::vector<std::string> answers;
    std::string answer1 = jsonData["results"][3].get("correct_answer", " ").asString();
    std::string answer2 = jsonData["results"][3].get("incorrect_answers", " ")[0].asString();
    std::string answer3 = jsonData["results"][3].get("incorrect_answers", " ")[1].asString();
    std::string answer4 = jsonData["results"][3].get("incorrect_answers", " ")[2].asString();
    answers.clear();
    answers.push_back(answer1);
    answers.push_back(answer2);
    answers.push_back(answer3);
    answers.push_back(answer4);
    std::shuffle(std::begin(answers), std::end(answers), rng);
    REQUIRE((answers[0] != answer1 || answers[1] != answer2)
            || (answers[3] != answer3 || answers[4] != answer4));
}
