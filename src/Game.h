//
// Created by Aaryan Gulia on 31/01/2024.
//

#ifndef PRISON_AURELIUS_GAME_H
#define PRISON_AURELIUS_GAME_H
#include "raylib.h"
#include "iostream"
#include "Screens/PauseScreen.h"

class Game {
protected:
    enum GameState{
        Menu = 0,
        Play = 1,
        Pause = 2
    }gameState;
    int width;
    int height;
    int FPS;
    const char* title;
public:
    Game();
    void virtual runGame();
    ~Game(){
        CloseWindow();
    }
};


#endif //PRISON_AURELIUS_GAME_H
