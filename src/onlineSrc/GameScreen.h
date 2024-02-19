#include "Screens/GameScreen.h"
#include "onlineSrc/Bat.h"

class GameScreenOnline : public GameScreen {
private:
    BatOnline bat1Online;
    BatOnline bat2Online;
    int playerNum;
public:
    GameScreenOnline(int screenWidth, int screenHeight,int screenFPS, const char* title)
            : GameScreen(screenWidth, screenHeight, screenFPS, title),
              bat1Online(BatOnline(20, screenHeight/2-50, 25, 10, 100)),
              bat2Online(BatOnline(screenWidth-20, screenHeight/2-50, 25, 10, 100)) {
        if (bat1Online.Connect("localhost", 60000)) {
            std::cout << "Connected to server." << std::endl;
        } else {
            std::cerr << "Failed to connect to server." << std::endl;
            return;
        }
        olc::net::message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::LookForGames;
        bat1Online.Send(msg);
        while (true) {
            if (bat1Online.Incoming().empty()) {
                std::cout << "No messages received from server." << std::endl;
            } else {
                std::cout << "Message received from server." << std::endl;
                break;
            }
        }
        auto serverMsg = bat1Online.Incoming().pop_back().msg;
        std::cout << "Server response " << int(serverMsg.header.id) << std::endl;
        if (serverMsg.header.id == CustomMsgTypes::JoinGame) {
            std::cout << "Joining game" << std::endl;
            olc::net::message<CustomMsgTypes> msg;
            msg.header.id = CustomMsgTypes::Quit;
            bat1Online.Send(msg);
            bat1Online.Disconnect();
            bat2Online.Connect("localhost", 60000);
            playerNum = 2;
        }
        else if (serverMsg.header.id == CustomMsgTypes::MakeNewGame) {
            std::cout << "Making game" << std::endl;
            playerNum = 1;
        }
    }

    void waitForReady(BatOnline bat){
        while (true) {
            if (bat.Incoming().pop_back().msg.header.id == CustomMsgTypes::Ready) {
                break;
            }
        }
    }

    bool handleInput() override {
        if(playerNum == 2){
            if(ball.checkBatCollision(bat1Online.getXPos(), bat1Online.getYPos(), bat1Online.getWidth(), bat1Online.getHeight(),1)){
                bat1Online.incrementScore();
            }
            if(ball.checkBatCollision(bat2Online.getXPos(), bat2Online.getYPos(), bat2Online.getWidth(), bat2Online.getHeight(),2)){
                bat2Online.incrementScore();
            }
            if(ball.checkWallCollision(width, height)){
                ball.move();
                countDown = 4;
            }
            ball.move();
        }
        olc::net::message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::move;
        float batPos = playerNum == 1? bat1Online.getYPos() : bat2Online.getYPos();
        msg << batPos;
        if(playerNum==2){msg<<bat1Online.getScore()<<bat2Online.getScore()<<ball.getXPos()<<ball.getYPos();}
        msg<<playerNum;
        playerNum == 1? bat1Online.Send(msg) : bat2Online.Send(msg);


        if(playerNum == 1){
            if(bat1Online.Incoming().empty()){
                return true;
            }
        }
        else{
            if(bat2Online.Incoming().empty()){
                return true;
            }
        }

        playerNum == 1? bat1Online.handleInput(1) : bat2Online.handleInput(1);


        auto serverMsg = playerNum == 1? bat1Online.Incoming().pop_front().msg : bat2Online.Incoming().pop_front().msg;
        int serverPlayerNum;
        serverMsg >> serverPlayerNum;
        if(serverPlayerNum == 2){
            bat1Online.m_qMessagesIn.clear();
            float ballXPos, ballYPos;
            int p1_score, p2_score;
            serverMsg >>ballYPos>>ballXPos>>p1_score>>p2_score>>batPos;
            bat2Online.setYPos(batPos);
            bat1Online.setScore(p1_score);
            bat2Online.setScore(p2_score);
            ball.setXPos(ballXPos);
            ball.setYPos(ballYPos);
        }else if(serverPlayerNum == 1){
            bat2Online.m_qMessagesIn.clear();
            serverMsg>>batPos;
            bat1Online.setYPos(batPos);
        }
        if(IsKeyPressed(KEY_P)){
            return false;
        }
        return true;
    }

    void draw() override {
        std::string text = "Difficuly: " + gameDiff;
        int textWidth = MeasureText(text.c_str(), 25);
        int x = width / 2 - textWidth / 2;
        int y = 15; // 50 pixels from the top of the screen
        DrawText(text.c_str(), x, y, 25, LIGHTGRAY);
        textWidth = MeasureText("Press P to Pause", 15);
        x = width / 2 - textWidth / 2;
        y = height - 40; // 50 pixels from the top of the screen
        DrawText("Press P to Pause", x, y, 15, LIGHTGRAY);
        DrawText(std::to_string(bat1Online.getScore()).c_str(), width / 4 - 25, 10, 40, BLACK);
        DrawText(std::to_string(bat2Online.getScore()).c_str(), width * 3 / 4 - 25, 10, 40, BLACK);

        bat1Online.draw();
        bat2Online.draw();
        ball.draw();
    }

    void updateBatPosition(CustomMsgTypes type, int batNumber) {
        if (batNumber == 1) {
            bat1Online.updatePosition(type);
        } else if (batNumber == 2) {
            bat2Online.updatePosition(type);
        }
    }

    void connectToServer(const std::string& host, const uint16_t port) {
        bat1Online.Connect(host, port);
        bat2Online.Connect(host, port);
    }
};