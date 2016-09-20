#include "Server.h"

int main() {

    Server *server = new Server();
    server->listen(8001);
    server->start_accept();
    server->run_thread()->join();
}