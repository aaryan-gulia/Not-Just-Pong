#include "StartScreen.h"
#include "Assets/Bat.h"
#include "Assets/Ball.h"

class GameScreen : public Screen {
protected:
    std::string gameDiff;
    float AI_accuracy;
    int countDown = 4;
public:
    Bat bat1, bat2;
    Ball ball;
    GameScreen(int screenWidth, int screenHeight,int screenFPS, const char* title);
    void setDiff(std::string diff);
    void setGame();
    bool virtual handleInput();
    void virtual draw();
    void reset();
};