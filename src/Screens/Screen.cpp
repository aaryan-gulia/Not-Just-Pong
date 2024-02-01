//
// Created by Aaryan Gulia on 31/01/2024.
//

#include "Screen.h"

Screen::Screen(int screenWidth, int screenHeight,int screenFPS, const char* title) {
    width = screenWidth;
    height = screenHeight;
    FPS = screenFPS;
    this->title = title;
}