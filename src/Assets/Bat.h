//
// Created by Aaryan Gulia on 31/01/2024.
//

#ifndef PRISON_AURELIUS_BAT_H
#define PRISON_AURELIUS_BAT_H
#include "raylib.h"
#include "string"

class Bat {
private:
    float xPos, yPos;
    float speed;
    int width, height;
    int score;

public:
    Bat(float xPos, float yPos, float speed, int width, int height);
    void moveUp();
    void moveDown();
    void virtual handleInput(int player);
    void draw();
    void reset();
    float getXPos();
    float getYPos();
    int getWidth();
    int getHeight();
    int getScore();
    void incrementScore();
    void AI(int ballYPos, int ballXPos, float accuracy);
};


#endif //PRISON_AURELIUS_BAT_H
