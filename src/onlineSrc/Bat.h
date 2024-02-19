//
// Created by Aaryan Gulia on 02/02/2024.
//

#ifndef PONG_BAT_H
#define PONG_BAT_H
#include "Assets/Bat.h"
#include "server/Client.h"


enum class CustomMsgTypes : uint32_t
{
    move,
    UpdateScreen,
    LookForGames,
    MakeNewGame,
    JoinGame,
    Ready,
    Wait,
    Quit
};

class BatOnline : public Bat, public olc::net::client_interface<CustomMsgTypes> {
public:
    BatOnline(float xPos, float yPos, float speed, int width, int height)
            : Bat(xPos, yPos, speed, width, height), olc::net::client_interface<CustomMsgTypes>() {
    }

    ~BatOnline(){
        if (IsConnected()) {
            // Send a ClientQuit message to the server
            olc::net::message<CustomMsgTypes> msg;
            msg.header.id = CustomMsgTypes::Quit;
            Send(msg);

            // Disconnect from the server
            Disconnect();
        }
    }



    void handleInput(int player) override {
        float oldYPos = yPos;
        if (player == 1) {
            if (IsKeyDown(KEY_W)) {
                moveUp();
            }
            if (IsKeyDown(KEY_S)) {
                moveDown();
            }
            if(yPos < 0 || yPos > GetScreenHeight() - height){
                yPos = oldYPos;
            }
        }

    }
    void handleInput(BatOnline& bat){
        if(bat.Incoming().empty()){
            return;
        }
        else{
            auto msg = bat.Incoming().pop_front().msg;
            msg >> yPos;
        }
    }

    void updatePosition(CustomMsgTypes type) {
        if (type == CustomMsgTypes::move) {
            Bat::moveUp();
        } else if (type == CustomMsgTypes::move) {
            Bat::moveDown();
        }
    }
};

#endif //PONG_BAT_H