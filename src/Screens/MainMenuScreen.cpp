//
// Created by Aaryan Gulia on 01/02/2024.
//

#include "MainMenuScreen.h"
#include "iostream"

GameState gameState = MainMenu;
GameMode gameMode;
Speed gameSpeed;
Difficulty aiDifficulty;
OnlineState onlineState;

GameState getGameState() {
    return gameState;
}
GameMode getGameMode() {
    return gameMode;
}
Speed getGameSpeed() {
    return gameSpeed;
}
Difficulty getAIDifficulty() {
    return aiDifficulty;
}
OnlineState getOnlineState() {
    return onlineState;
}
void setGameState(GameState state) {
    gameState = state;
}
void setGameMode(GameMode mode) {
    gameMode = mode;
}
void setGameSpeed(Speed speed) {
    gameSpeed = speed;
}
void setAIDifficulty(Difficulty difficulty) {
    aiDifficulty = difficulty;
}
void setOnlineState(OnlineState state) {
    onlineState = state;
}

MainMenuScreen::MainMenuScreen(int screenWidth, int screenHeight,int screenFPS, const char* title):
        Screen(screenWidth,screenHeight,screenFPS,title){}

bool MainMenuScreen::handleInput() {
    auto key = GetKeyPressed();
    switch(key){
        case KEY_UP:
            selectedOption--;
            if (selectedOption < 0) {
                selectedOption = options.size() - 1;
            }
            break;
        case KEY_DOWN:
            selectedOption++;
            if (selectedOption >= options.size()) {
                selectedOption = 0;
            }
            break;
        case KEY_ENTER:
            switch(gameState){
                case MainMenu:{
                    switch(selectedOption){
                        case 0:{
                            gameMode = Online;
                            gameState = OnlineMenu;
                            options = {"Create Game","Join Game","Back"};
                            return true;
                        }
                        case 1:{
                            gameMode = AI;
                            gameState = SpeedMenu;
                            options = {"Slow","Medium","Fast","Insane","Back"};
                            //options = {"Easy","Medium","Hard","Brutal","Back"};
                            return true;
                        }
                        case 2:{
                            gameMode = TwoPlayer;
                            gameState = SpeedMenu;
                            options = {"Slow","Medium","Fast","Insane","Back"};
                            return true;
                        }
                        case 3:{
                            gameState = Exit;
                            return false;
                        }
                    }
                    break;
                }
                case SpeedMenu:{
                    switch(selectedOption){
                        case 0:{
                            gameSpeed = Slow;
                            break;
                        }
                        case 1:{
                            gameSpeed = Medium;
                            break;
                        }
                        case 2:{
                            gameSpeed = Fast;
                            break;
                        }
                        case 3:{
                            gameSpeed = Insane;
                            std::cout<<"Setting Insane Speed"<<std::endl;
                            break;
                        }
                        case 4:{
                            gameState = MainMenu;
                            options = {"Online","AI","2-Player","Exit"};
                            return true;
                        }
                    }
                    switch (gameMode){
                        case AI:{
                            gameState = AIMenu;
                            options = {"Easy","Medium","Hard","Brutal","Back"};
                            return false;
                        }
                        case TwoPlayer:{
                            gameState = Play;
                            return false;
                        }
                        case Online:{
                            gameState = Play;
                            return false;
                        }
                    }
                }
                case AIMenu:{
                    switch(selectedOption) {
                        case 0: {
                            aiDifficulty = Easy;
                            gameState = Play;
                            return true;
                        }
                        case 1: {
                            aiDifficulty = Med;
                            gameState = Play;
                            return true;
                        }
                        case 2: {
                            aiDifficulty = Hard;
                            gameState = Play;
                            return true;
                        }
                        case 3: {
                            aiDifficulty = Brutal;
                            gameState = Play;
                            return true;
                        }
                        case 4: {
                            gameState = SpeedMenu;
                            options = {"Slow", "Medium", "Fast", "Insane", "Back"};
                            return true;
                        }
                    }
                }
                case OnlineMenu:{
                    switch(selectedOption){
                        case 0:{
                            onlineState = Host;
                            gameState = SpeedMenu;
                            options = {"Slow","Medium","Fast","Insane","Back"};
                            return true;
                        }
                        case 1:{
                            onlineState = Join;
                            return false;
                        }
                        case 2:{
                            gameState = MainMenu;
                            options = {"Online","AI","2-Player","Exit"};
                            return true;
                        }
                    }

                }
            }
            break;
        default:
            return true;
    }
    return true;
}

void MainMenuScreen::draw(){
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
