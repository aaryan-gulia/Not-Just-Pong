//
// Created by Aaryan Gulia on 31/01/2024.
//

#ifndef PRISON_AURELIUS_GAME_H
#define PRISON_AURELIUS_GAME_H
#include "raylib.h"

class Game {
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
    void runGame();
    ~Game(){
        CloseWindow();
    }
};


#endif //PRISON_AURELIUS_GAME_H
