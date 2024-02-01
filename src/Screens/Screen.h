#include "raylib.h"
#include "Assets/Bat.h"
#include "Assets/Ball.h"
#include "string"

class Screen {
public:
    int width;
    int height;
    int FPS;
    const char* title = "Pong";
    Screen(int screenWidth, int screenHeight,int screenFPS, const char* title);
};