//
// Created by Aaryan Gulia on 31/01/2024.
//

#include "GameScreen.h"
#include <thread>
#include <chrono>

GameScreen::GameScreen(int screenWidth, int screenHeight,int screenFPS, const char* title):
        Screen(screenWidth,screenHeight,screenFPS,title),ball(Ball(screenWidth/2, screenHeight/2, -10, -10, 10)),
        bat1(Bat(20, screenHeight/2-50, 25, 10, 100)),bat2(Bat(screenWidth-20, screenHeight/2-50, 25, 10, 100)){
}

bool GameScreen::handleInput() {
    // Handle user input for the game
    if(countDown>0){return true;}
    bat1.handleInput(1);
    bat2.AI(ball.getYPos(), ball.getXPos(),AI_accuracy);
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

    return true;
}

void GameScreen::setDiff(std::string diff) {
    gameDiff = diff;

    int ballSpeed;
    if(diff == "Easy"){
        ballSpeed = 10;
        AI_accuracy = 0.3;
    }
    else if(diff == "Medium"){
        ballSpeed = 15;
        AI_accuracy = 0.5;
    }
    else if(diff == "Hard"){
        ballSpeed = 20;
        AI_accuracy = 0.75;
    }
    else if(diff == "Brutal"){
        ballSpeed = 25;
        AI_accuracy = 0.9;
    }
    ball.setXSpeed(ballSpeed);
    ball.setYSpeed(ballSpeed);
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

void GameScreen::reset() {
    ball.reset(width, height);
    bat1.reset();
    bat2.reset();
}