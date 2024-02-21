#include "server/olc_net.h"
#include "Assets/Bat.h"

class ServerGame : public olc::net::server_interface<CustomMsgTypes> {
public:
    ServerGame(uint16_t port) : olc::net::server_interface<CustomMsgTypes>(port) {}

    bool OnClientConnect(std::shared_ptr<olc::net::connection<CustomMsgTypes>> client) override {
        std::cout << "New client connected [" << client->GetID() << "]\n";
        return true;
    }

    void OnClientDisconnect(std::shared_ptr<olc::net::connection<CustomMsgTypes>> client) override {
        std::cout << "Removing client [" << client->GetID() << "]\n";
        m_deqConnections.erase(std::remove(m_deqConnections.begin(), m_deqConnections.end(), client), m_deqConnections.end());
    }

    float bat1YPos = 0;
    float bat2YPos = 0;
    float ballXPos = 0;
    float ballYPos = 0;
    int p1Score = 0;
    int p2Score = 0;
    int p2Counter = 0;
    int p1Counter = 0;

    void OnMessage(std::shared_ptr<olc::net::connection<CustomMsgTypes>> client, olc::net::message<CustomMsgTypes>& msg) override {
        if(msg.header.id == CustomMsgTypes::move){
            int player;
            msg >> player;
            olc::net::message<CustomMsgTypes> gameState;

            if (player == 2) {
                msg >> ballYPos>>ballXPos>>p1Score>>p2Score;
                msg>>bat2YPos;
                gameState.header.id = CustomMsgTypes::UpdateScreen;
                gameState<<bat2YPos<<p1Score<<p2Score<<ballXPos<<ballYPos<<player;
            } else if(player == 1) {
                msg>>bat1YPos;
                gameState.header.id = CustomMsgTypes::UpdateScreen;
                gameState<<bat1YPos<<player;
            }
            m_qMessagesIn.clear();
            //std::cout << "sends to p1: " << p2Counter << ", sends to p2 " << p1Counter << std::endl;
            for_each(m_deqConnections.begin(), m_deqConnections.end(), [&](std::shared_ptr<olc::net::connection<CustomMsgTypes>> conn) {
                if (conn != client) {
                    conn->Send(gameState);
                }
            });
            return;
        }
        else if (msg.header.id == CustomMsgTypes::Ready) {
            olc::net::message<CustomMsgTypes> gameState;
            gameState.header.id = CustomMsgTypes::Ready;
            std::cout << "Game is ready" << std::endl;
            MessageAllClients(gameState);
            return;
        }
        else if(msg.header.id == CustomMsgTypes::MakeNewGame){
            olc::net::message<CustomMsgTypes> newMsg;
            newMsg.header.id = CustomMsgTypes::Wait;
            client->Send(newMsg);
        }
        else if(msg.header.id == CustomMsgTypes::JoinGame){
            olc::net::message<CustomMsgTypes> newMsg;
            newMsg.header.id = CustomMsgTypes::Ready;
            std::cout<<"Game is ready"<<std::endl;
            MessageAllClients(newMsg);
        }
        else if (msg.header.id == CustomMsgTypes::LookForGames) {
            std::cout << "Client looking for games" << std::endl;
            if (m_deqConnections.size()%2 == 1) {
                std::cout << "No games found" << std::endl;
                olc::net::message<CustomMsgTypes> newMsg;
                newMsg.header.id = CustomMsgTypes::Wait;
                std::cout << "Sending message " << int(newMsg.header.id) << std::endl;
                client->Send(newMsg);
                m_qMessagesIn.clear();
            } else {
                std::cout << "Game found" << std::endl;
                olc::net::message<CustomMsgTypes> newMsg;
                newMsg.header.id = CustomMsgTypes::Wait;
                std::cout << "Sending message " << int(newMsg.header.id) << std::endl;
                client->Send(newMsg);
                m_qMessagesIn.clear();
            }
        }else if (msg.header.id == CustomMsgTypes::Quit){
            m_deqConnections.erase(std::remove(m_deqConnections.begin(), m_deqConnections.end(), client), m_deqConnections.end());
            olc::net::message<CustomMsgTypes> newMsg;
            newMsg.header.id = CustomMsgTypes::Quit;
            MessageAllClients(newMsg);
        }
    }
};