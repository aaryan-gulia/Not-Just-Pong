#include "raylib.h"
#include "MainMenuScreen.h"

class StartScreen : public Screen {
private:
    int selectedOption = 0;
    std::vector<std::string> options = {"Easy", "Medium", "Hard", "Brutal"};
public:
    StartScreen(int screenWidth, int screenHeight,int screenFPS, const char* title);
    std::string gameDiff;
    bool handleInput();
    void draw();
};