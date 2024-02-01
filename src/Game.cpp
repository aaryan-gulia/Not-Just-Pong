//
// Created by Aaryan Gulia on 31/01/2024.
//
#include "iostream"
#include "Game.h"
#include "Screens/PauseScreen.h"


Game::Game() {
    std::cout<<"Starting Game!"<<std::endl;
    width = 1000;
    height = width * 9 /16;
    FPS = 60;
    title = "Pong";
    InitWindow(width, height, title);
    InitAudioDevice();
    SetTargetFPS(30);
    gameState = Menu;

}

void Game::runGame() {
    StartScreen startScreen(width,height,FPS,title);
    GameScreen gameScreen(width,height,FPS,title);
    PauseScreen pauseScreen(width,height,FPS,title);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);
        if(gameState == Menu){
            startScreen.draw();
            if(!startScreen.handleInput()){
                gameState = Play;
                gameScreen.setDiff(startScreen.gameDiff);
            }
        }
        else if(gameState == Play){
            gameScreen.draw();
            if(!gameScreen.handleInput()){
                gameState = Pause;
            }
        }
        else if(gameState == Pause){
            pauseScreen.draw();
            if(!pauseScreen.handleInput()){
                if(pauseScreen.state == "Restart"){
                    gameScreen.reset();
                    gameState = Menu;
                }
                else if(pauseScreen.state == "Menu"){
                    gameState = Menu;
                }
                else if(pauseScreen.state == "Play"){
                    gameState = Play;
                }
            }
        }
        EndDrawing();
    }
}