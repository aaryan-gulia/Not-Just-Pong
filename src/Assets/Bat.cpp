//
// Created by Aaryan Gulia on 31/01/2024.
//

#include "Bat.h"

Bat::Bat(float xPos, float yPos, float speed, int width, int height) {
    this->xPos = xPos;
    this->yPos = yPos;
    this->speed = speed;
    this->width = width;
    this->height = height;
    this->score = 0;
}

void Bat::moveDown() {
    yPos += speed;
}
void Bat::moveUp() {
    yPos -= speed;
}
void Bat::handleInput(int player) {
    float oldYPos = yPos;
    if(player == 1){
        if (IsKeyDown(KEY_W)) {
            moveUp();
        }
        if (IsKeyDown(KEY_S)) {
            moveDown();
        }
    }
    if(player == 2){
        if (IsKeyDown(KEY_UP)) {
            moveUp();
        }
        if (IsKeyDown(KEY_DOWN)) {
            moveDown();
        }
    }
    if(yPos < 0 || yPos > GetScreenHeight() - height){
        yPos = oldYPos;
    }
}

void Bat::AI(int ballYPos, int ballXPos, float accuracy) {
    float oldYPos = yPos;
    float randomFloat = GetRandomValue(0,10000)/10000.0f;
    if(ballXPos > GetScreenWidth()/2 && ballYPos < (yPos+height/2) && randomFloat < accuracy){
        moveUp();
    }
    else if(ballXPos > GetScreenWidth()/2 && ballYPos > (yPos-height/2) && randomFloat < accuracy){
        moveDown();
    }
    if(yPos < 0 || yPos > GetScreenHeight() - height){
        yPos = oldYPos;
    }
}

//void Bat::setupOnlineBat() {
//    this->Connect("localhost", 60000);
//}
//void Bat::disconnectOnlineBat() {
//    if (IsConnected()) {
//        // Send a ClientQuit message to the server
//        olc::net::message<CustomMsgTypes> msg;
//        msg.header.id = CustomMsgTypes::Quit;
//        Send(msg);
//
//        // Disconnect from the server
//        Disconnect();
//    }
//}

void Bat::incrementScore() {
    score++;
}

void Bat::draw() {
    DrawRectangle(xPos, yPos, width, height, BLACK);
}
float Bat::getXPos() {
    return xPos;
}
float Bat::getYPos() {
    return yPos;
}
int Bat::getWidth() {
    return width;
}
int Bat::getHeight() {
    return height;
}
int Bat::getScore() {
    return score;
}

void Bat::reset() {
    yPos = GetScreenHeight()/2 - height/2;
    score = 0;
}

void Bat::setXPos(float xPos) {
    this->xPos = xPos;
}
void Bat::setYPos(float yPos) {
    this->yPos = yPos;
}
void Bat::setScore(int score) {
    this->score = score;
}