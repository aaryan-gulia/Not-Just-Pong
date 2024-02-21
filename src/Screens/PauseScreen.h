//
// Created by Aaryan Gulia on 31/01/2024.
//

#ifndef PRISON_AURELIUS_PAUSESCREEN_H
#define PRISON_AURELIUS_PAUSESCREEN_H
#include "vector"
#include "GameScreen.h"

class PauseScreen: public Screen{
private:
    int selectedOption = 0;
    std::vector<std::string> options = {"Resume", "Exit"};

public:
    std::string state;
    PauseScreen(int width, int height, int FPS, const char* title);
    bool handleInput();
    void draw();
};


#endif //PRISON_AURELIUS_PAUSESCREEN_H
