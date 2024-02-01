#include "StartScreen.h"
#include "Assets/Bat.h"
#include "Assets/Ball.h"

class GameScreen : public Screen {
private:
    std::string gameDiff;
    float AI_accuracy;
public:
    Bat bat1, bat2;
    Ball ball;
    GameScreen(int screenWidth, int screenHeight,int screenFPS, const char* title);
    void setDiff(std::string diff);
    bool handleInput();
    void draw();
    void reset();
};