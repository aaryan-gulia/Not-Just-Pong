//
// Created by Aaryan Gulia on 02/02/2024.
//

#include "GameOnline.h"

void GameOnline::runGame() {
    GameScreenOnline gameScreen(width,height,FPS,title);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);

        if(gameState == Pause){
            EndDrawing();
            continue;
        }
        gameScreen.draw();
        if(!gameScreen.handleInput()){
                gameState = Pause;
        }
        EndDrawing();
    }
}