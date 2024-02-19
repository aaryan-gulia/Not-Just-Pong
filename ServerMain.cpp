#include "onlineSrc/ServerGame.h"

int main() {
    ServerGame server(60000);
    server.Start();

    while (1) {
        server.Update(-1, true);
    }
    return 0;
}