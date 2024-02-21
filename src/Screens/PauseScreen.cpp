//
// Created by Aaryan Gulia on 31/01/2024.
//

#include "PauseScreen.h"
PauseScreen::PauseScreen(int width, int height, int FPS, const char* title):Screen(width,height,FPS,title) {
}

bool PauseScreen::handleInput() {
    if (IsKeyPressed(KEY_UP)) {
        selectedOption--;
        if (selectedOption < 0) {
            selectedOption = options.size() - 1;
        }
    }
    if (IsKeyPressed(KEY_DOWN)) {
        selectedOption++;
        if (selectedOption >= options.size()) {
            selectedOption = 0;
        }
    }
    if (IsKeyPressed(KEY_ENTER)) {
        if(options[selectedOption]=="Resume"){
            gameState = Play;
            return false;
        }
        else if(options[selectedOption]=="Exit"){
            gameState = MainMenu;
            return false;
        }
    }
    return true;
}

void PauseScreen::draw(){
    int i =0;
    for (auto option: options) {
        Color color = option == options[selectedOption] ? RED : BLACK;
        int textWidth = MeasureText(option.c_str(), 50);
        int textHeight = 50; // Assuming the height of the text is 50
        int x = width/2 - textWidth/2;
        int y = height/2 - textHeight/2 + 100*(i++ - options.size()/2);
        DrawText(option.c_str(), x, y, 50, color);
    }
}