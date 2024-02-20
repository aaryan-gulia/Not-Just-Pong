//
// Created by Aaryan Gulia on 01/02/2024.
//

#ifndef PONG_MAINMENUSCREEN_H
#define PONG_MAINMENUSCREEN_H
#include "string"
#include "Screen.h"
#include "raylib.h"
//#include "Assets/GameState.h"


enum GameState{
    MainMenu = 0,
    AIMenu = 1,
    OnlineMenu = 2,
    TwoPlayerMenu = 3,
    SpeedMenu = 4,
    Play = 5,
    Pause = 6,
    Exit = 7
};

enum GameMode {
    AI = 0,
    Online = 1,
    TwoPlayer = 2
};

enum Speed{
    Slow = 0,
    Medium = 1,
    Fast = 2,
    Insane = 4
};

enum Difficulty{
    Easy = 0,
    Med = 1,
    Hard = 2,
    Brutal = 3
};

enum OnlineState{
    Host = 0,
    Join = 1
};

extern GameState gameState;
extern GameMode gameMode;
extern Speed gameSpeed;
extern Difficulty aiDifficulty;
extern OnlineState onlineState;

GameState getGameState();
GameMode getGameMode();
Speed getGameSpeed();
Difficulty getAIDifficulty();
OnlineState getOnlineState();
void setGameState(GameState state);
void setGameMode(GameMode mode);
void setGameSpeed(Speed speed);
void setAIDifficulty(Difficulty difficulty);
void setOnlineState(OnlineState state);

class MainMenuScreen: public Screen{
public:
    MainMenuScreen(int screenWidth, int screenHeight,int screenFPS, const char* title);

    std::vector<std::string> options = {"Online","AI","2-Player","Exit"};
    int selectedOption = 0;
    bool handleInput();
    void draw();

};


#endif //PONG_MAINMENUSCREEN_H
