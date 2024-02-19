//
// Created by Aaryan Gulia on 31/01/2024.
//

#ifndef PRISON_AURELIUS_BALL_H
#define PRISON_AURELIUS_BALL_H
#include "raylib.h"

class Ball {
protected:
    float xPos, yPos;
    float xSpeed, ySpeed;
    int radius;

public:
    Ball(float xPos, float yPos, float xSpeed, float ySpeed, int radius);
    Sound collisionSound;
    Sound exitScreenSound;
    void virtual move();
    void draw();
    void reset(int screenWidth, int screenHeight);
    bool virtual checkBatCollision(int batX, int batY, int batWidth, int batHeight, int player);
    bool virtual checkWallCollision(int screenWidth, int screenHeight);
    float getXPos();
    float getYPos();
    int getRadius();
    void setXSpeed(float xSpeed);
    void setYSpeed(float ySpeed);
    void setXPos(float xPos);
    void setYPos(float yPos);
    float getXSpeed();
    float getYSpeed();
    ~Ball(){
        UnloadSound(collisionSound);
        UnloadSound(exitScreenSound);
    }
};


#endif //PRISON_AURELIUS_BALL_H
