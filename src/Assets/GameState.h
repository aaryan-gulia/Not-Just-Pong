//
// Created by Aaryan Gulia on 20/02/2024.
//

#ifndef PONG_GAMESTATE_H
#define PONG_GAMESTATE_H


class GameState {
public:
    enum State{
        MainMenu = 0,
        AIMenu = 1,
        OnlineMenu = 2,
        TwoPlayerMenu = 3,
        SpeedMenu = 4,
        Play = 5,
        Pause = 6,
        Exit = 7
    }gameState=MainMenu;

    enum GameMode {
        AI = 0,
        Online = 1,
        TwoPlayer = 2
    }gameMode;

    enum Speed{
        Slow = 0,
        Medium = 1,
        Fast = 2,
        Insane = 4
    }gameSpeed;

    enum Difficulty{
        Easy = 0,
        Med = 1,
        Hard = 2,
        Brutal = 3
    }aiDifficulty;

    enum OnlineState{
        Host = 0,
        Join = 1
    }onlineState;

};


#endif //PONG_GAMESTATE_H
