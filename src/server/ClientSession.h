#ifndef PONG_CLIENTSESSION_H
#define PONG_CLIENTSESSION_H

#include <iostream>
#include "olc_net.h"

enum class CustomMsgTypes : uint32_t
{
    moveUp,
    moveDown
};

class CustomClient : public olc::net::client_interface<CustomMsgTypes>
{
public:
    void moveUp()
    {
        olc::net::message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::moveUp;
        Send(msg);
    }
    void moveDown()
    {
        olc::net::message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::moveDown;
        Send(msg);
    }
};

#endif //PONG_CLIENTSESSION_H