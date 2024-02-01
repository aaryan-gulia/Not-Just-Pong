//
// Created by Aaryan Gulia on 31/01/2024.
//

#include "StartScreen.h"

StartScreen::StartScreen(int screenWidth, int screenHeight,int screenFPS, const char* title):
        Screen(screenWidth,screenHeight,screenFPS,title){}

bool StartScreen::handleInput() {
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
    if (IsKeyPressed(KEY_ENTER) &&
    (options[selectedOption] == "Easy"|| options[selectedOption] == "Medium" || options[selectedOption] == "Hard" || options[selectedOption] == "Brutal")) {
        gameDiff = options[selectedOption];
        selectedOption = 0;
        options = {"Play", "Back"};
    }
    else if(IsKeyPressed(KEY_ENTER) && options[selectedOption]=="Play"){
        options = {"Easy","Medium","Hard","Brutal"};
        return false;
    }
    else if(IsKeyPressed(KEY_ENTER) && options[selectedOption]=="Back"){
        options = {"Easy","Medium","Hard","Brutal"};
    }
    return true;
}

void StartScreen::draw(){
    // Draw start screen
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
