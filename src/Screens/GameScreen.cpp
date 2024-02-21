//
// Created by Aaryan Gulia on 31/01/2024.
//

#include "GameScreen.h"
#include <iostream>
#include <thread>
#include <chrono>

GameScreen::GameScreen(int screenWidth, int screenHeight,int screenFPS, const char* title):
        Screen(screenWidth,screenHeight,screenFPS,title),ball(Ball(screenWidth/2, screenHeight/2, -10, -10, 10)),
        bat1(Bat(20, screenHeight/2-50, 25, 10, 100)),bat2(Bat(screenWidth-20, screenHeight/2-50, 25, 10, 100)){
}

bool GameScreen::handleInput() {
    // Handle user input for the game
    if(countDown>0){
        draw();
        return true;}
    bat1.handleInput(1);
    gameMode == AI? bat2.AI(ball.getYPos(), ball.getXPos(),AI_accuracy): bat2.handleInput(2);
    if(ball.checkBatCollision(bat1.getXPos(), bat1.getYPos(), bat1.getWidth(), bat1.getHeight(),1)){
        bat1.incrementScore();
    }
    if(ball.checkBatCollision(bat2.getXPos(), bat2.getYPos(), bat2.getWidth(), bat2.getHeight(),2)){
        bat2.incrementScore();
    }
    if(ball.checkWallCollision(width, height)){
        ball.move();
        countDown = 4;
    }
    ball.move();
    if(IsKeyPressed(KEY_P)){
        countDown = 4;
        return false;
    }
    draw();
    return true;
}

enum onlineGameStates{
    Wait = 0,
    Start = 1,
    Stop = 2,
    Quit = 3
}onlineGameStates;

bool GameScreen::handleOnlineInput() {
    switch (onlineGameStates) {
        case Wait:{
            draw("wait");
            break;
        }
        case Start:{
            break;
        }
        case Stop:{
            draw("pause");
            if(IsKeyPressed(KEY_P)){
                olc::net::message<CustomMsgTypes> msg;
                msg.header.id = CustomMsgTypes::Ready;
                if(onlineState == Host){
                    bat1.Send(msg);
                }
                else{
                    bat2.Send(msg);
                }
                onlineGameStates = Start;
            }
            return true;
        }
        case Quit:{
            return false;
        }
    }
    std::cout<<"Online Game State: "<<onlineGameStates<<std::endl;
    olc::net::message<CustomMsgTypes> msg;
    msg.header.id = CustomMsgTypes::move;
    if(onlineState == Host){
        msg<<bat1.getYPos();
        msg<<int(1);
        if(bat1.Incoming().empty()){
            return true;
        }
        switch(bat1.Incoming().front().msg.header.id){
            case CustomMsgTypes::Quit:{
                onlineGameStates = Quit;
                return false;
            }
            case CustomMsgTypes::Wait:{
                onlineGameStates = Wait;
                return true;
            }
            case CustomMsgTypes::Pause:{
                onlineGameStates = Stop;
                return true;
            }
            case CustomMsgTypes::Ready:{
                onlineGameStates = Start;
                return true;
            }
            default:{
                onlineGameStates = Start;
                break;
            }
        }

    }
    else{
        msg<<bat2.getYPos();
        msg<<bat1.getScore()<<bat2.getScore()<<ball.getXPos()<<ball.getYPos();
        msg<<int(2);
        if(bat2.Incoming().empty()){
            return true;
        }
        switch(bat2.Incoming().front().msg.header.id){
            case CustomMsgTypes::Quit:{
                onlineGameStates = Quit;
                return false;
            }
            case CustomMsgTypes::Wait:{
                onlineGameStates = Wait;
                return true;
            }
            case CustomMsgTypes::Pause:{
                onlineGameStates = Stop;
                return true;
            }
            case CustomMsgTypes::Ready:{
                onlineGameStates = Start;
                return true;
            }
            default:{
                onlineGameStates = Start;
                break;
            }
        }
    }
    if(onlineState == Host){
        ball.checkBatCollision(bat1.getXPos(), bat1.getYPos(), bat1.getWidth(), bat1.getHeight(),1);
        ball.checkBatCollision(bat2.getXPos(), bat2.getYPos(), bat2.getWidth(), bat2.getHeight(),2);
        ball.checkWallCollision(width, height);
    }
    auto serverMsg = onlineState == Host? bat1.Incoming().pop_back().msg: bat2.Incoming().pop_back().msg;
    if(serverMsg.header.id == CustomMsgTypes::UpdateScreen){
        std::cout<<"Update Screen Received"<<std::endl;
        onlineGameStates = Start;
        int serverPlayerNum,batPos;
        serverMsg >> serverPlayerNum;
        if(serverPlayerNum == 2){
            bat1.m_qMessagesIn.clear();
            float ballXPos, ballYPos;
            int p1_score, p2_score;
            serverMsg >>ballYPos>>ballXPos>>p1_score>>p2_score>>batPos;
            bat2.setYPos(batPos);
            bat1.setScore(p1_score);
            bat2.setScore(p2_score);
            ball.setXPos(ballXPos);
            ball.setYPos(ballYPos);
        }else if(serverPlayerNum == 1){
            bat2.m_qMessagesIn.clear();
            serverMsg>>batPos;
            bat1.setYPos(batPos);
        }
    }
    if(onlineState == Join){
        if(ball.checkBatCollision(bat1.getXPos(), bat1.getYPos(), bat1.getWidth(), bat1.getHeight(),1)){
            bat1.incrementScore();
        }
        if(ball.checkBatCollision(bat2.getXPos(), bat2.getYPos(), bat2.getWidth(), bat2.getHeight(),2)){
            bat2.incrementScore();
        }
        if(ball.checkWallCollision(width, height)){
            ball.move();
            countDown = 4;
        }
        ball.move();
    }
    draw();
    if(IsKeyPressed(KEY_P)){
        olc::net::message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::Pause;
        if(onlineState == Host){
            bat1.Send(msg);
        }
        else{
            bat2.Send(msg);
        }
        onlineGameStates = Stop;
    }
    return true;
}

void GameScreen::setGame() {
    std::cout<<"Setting Game With "<< getGameMode()<<" Mode, "<<getGameSpeed()<<" Speed, "<<getAIDifficulty()<<" Difficulty"<<std::endl;
    int ballSpeed;
    switch (getGameSpeed()) {
        case Slow:{
            ballSpeed = 10;
            break;
        }
        case Medium:{
            ballSpeed = 15;
            break;
        }
        case Fast:{
            ballSpeed = 20;
            break;
        }
        case Insane:{
            ballSpeed = 25;
            std::cout<<"Setting Insane Speed"<<std::endl;
            break;

        }
    }
    ball.setXSpeed(ballSpeed);
    ball.setYSpeed(ballSpeed);

    if(getGameMode() == AI){
        switch (getAIDifficulty()) {
            case Easy: {
                AI_accuracy = 0.3;
                break;
            }
            case Med: {
                AI_accuracy = 0.5;
                break;
            }
            case Hard: {
                AI_accuracy = 0.7;
                break;
            }
            case Brutal: {
                AI_accuracy = 0.9;
                std::cout<<"Setting Brutal AI"<<std::endl;
                break;
            }
        }
    }
    else if(getGameMode() == Online){
        if(onlineState == Host){
            bat1.setupOnlineBat();
            olc::net::message<CustomMsgTypes> msg;
            msg.header.id = CustomMsgTypes::MakeNewGame;
            bat1.Send(msg);
            onlineGameStates = Wait;
        }
        else if(onlineState == Join){
            bat2.setupOnlineBat();
            olc::net::message<CustomMsgTypes> msg;
            msg.header.id = CustomMsgTypes::JoinGame;
            bat2.Send(msg);
            onlineGameStates = Wait;
        }
    }
}

void GameScreen::draw() {
    std::string text = "Difficuly: " + gameDiff;
    int textWidth = MeasureText(text.c_str(), 25);
    int x = width / 2 - textWidth / 2;
    int y = 15; // 50 pixels from the top of the screen
    DrawText(text.c_str(), x, y, 25, LIGHTGRAY);
    textWidth = MeasureText("Press P to Pause", 15);
    x = width / 2 - textWidth / 2;
    y = height - 40; // 50 pixels from the top of the screen
    DrawText("Press P to Pause", x, y, 15, LIGHTGRAY);
    DrawText(std::to_string(bat1.getScore()).c_str(), width / 4 - 25, 10, 40, BLACK);
    DrawText(std::to_string(bat2.getScore()).c_str(), width * 3 / 4 - 25, 10, 40, BLACK);

    bat1.draw();
    bat2.draw();
    ball.draw();

    if (countDown > 0) {
        // Display the countdown
        std::string countdownText = std::to_string(countDown-1);
        int textWidth = MeasureText(countdownText.c_str(), 50);
        int x = width / 2 - textWidth / 2;
        int y = height / 2;
        DrawText(countdownText.c_str(), x, y, 100, GRAY);
        countDown--;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return;
    }else {
        int textWidth = MeasureText("Pong", 50);
        int x = width / 2 - textWidth / 2;
        int y = height / 2;
        DrawText("Pong", x, y, 50, LIGHTGRAY);
    }
}

void GameScreen::draw(std::string state){
    if(state == "wait"){
        std::string text = "Waiting for Player to Join";
        int textWidth = MeasureText(text.c_str(), 25);
        int x = width / 2 - textWidth / 2;
        int y = 15; // 50 pixels from the top of the screen
        DrawText(text.c_str(), x, y, 25, LIGHTGRAY);
    }
}

void GameScreen::reset() {
    ball.reset(width, height);
    bat1.reset();
    bat2.reset();
    if(gameMode == Online){
        if(onlineState == Host){
            olc::net::message<CustomMsgTypes> msg;
            msg.header.id = CustomMsgTypes::Quit;
            bat1.disconnectOnlineBat();
        }
        else if(onlineState == Join){
            olc::net::message<CustomMsgTypes> msg;
            msg.header.id = CustomMsgTypes::Quit;
            bat2.disconnectOnlineBat();
        }
    }
}

GameScreen::~GameScreen() {
    if(gameMode == Online){
        if(onlineState == Host){
            olc::net::message<CustomMsgTypes> msg;
            msg.header.id = CustomMsgTypes::Quit;
            bat1.disconnectOnlineBat();
        }
        else if(onlineState == Join){
            olc::net::message<CustomMsgTypes> msg;
            msg.header.id = CustomMsgTypes::Quit;
            bat2.disconnectOnlineBat();
        }
    }
}