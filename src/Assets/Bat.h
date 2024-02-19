//
// Created by Aaryan Gulia on 31/01/2024.
//

#ifndef PRISON_AURELIUS_BAT_H
#define PRISON_AURELIUS_BAT_H
#include "raylib.h"
#include "string"

class Bat {
protected:
    float xPos, yPos;
    float speed;
    int width, height;
    int score;

public:
    Bat(float xPos, float yPos, float speed, int width, int height);
    void virtual moveUp();
    void virtual moveDown();
    void virtual handleInput(int player);
    void draw();
    void reset();
    float getXPos();
    float getYPos();
    int getWidth();
    int getHeight();
    void setXPos(float xPos);
    void setYPos(float yPos);
    void setScore(int score);
    int getScore();
    void incrementScore();
    void AI(int ballYPos, int ballXPos, float accuracy);
};


#endif //PRISON_AURELIUS_BAT_H
