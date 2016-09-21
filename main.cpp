#include "Server.h"

#include <queue>
#include <memory>

constexpr uint N_THREADS = 2;

int main() {

    Server server;
    server.listen(8001);
    server.start_accept();

    std::queue<Server::thread_t> threads;

    for (uint n = 0; n < N_THREADS; n++)
        threads.push(server.run_thread());

    while (!threads.empty()) {
        auto thread = std::move(threads.front());
        thread->join();

        threads.pop();
    }
}