//
// Created by Aaryan Gulia on 31/01/2024.
//
#include "Game.h"


Game::Game() {
    std::cout<<"Starting Game!"<<std::endl;
    width = 1000;
    height = width * 9 /16;
    FPS = 60;
    title = "Pong";
    InitWindow(width, height, title);
    InitAudioDevice();
    SetTargetFPS(30);
    gameState = MainMenu;

}

void Game::runGame() {
    MainMenuScreen mainMenuScreen(width,height,FPS,title);
    StartScreen startScreen(width,height,FPS,title);
    GameScreen gameScreen(width,height,FPS,title);
    PauseScreen pauseScreen(width,height,FPS,title);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);

        if(gameState == Play){
            gameScreen.handleInput();
            gameScreen.draw();
        }
        else if(gameState == Pause){
            pauseScreen.handleInput();
            pauseScreen.draw();
        }
        else{
            mainMenuScreen.handleInput();
            mainMenuScreen.draw();
            if(gameState == Play){
                gameScreen.setGame();
            }
            else if(gameState == Exit){
                break;
            }
        }

        EndDrawing();
    }
}