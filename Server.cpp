#include "Server.h"

#include <iostream>

Server::Server() : WebsocketServer() {

    this->init_asio();
    this->set_message_handler(std::bind(&Server::on_message, this, std::placeholders::_1, std::placeholders::_2));
}

Server::~Server() {
}

std::unique_ptr<std::thread> Server::run_thread() {

    return std::make_unique<std::thread>([this]() -> void {

        std::cout << "thread #" << std::this_thread::get_id() << " started" << std::endl;

        this->run();
    });
}

void Server::on_message(Server* self, Connection handle, Server::message_ptr message) {

    std::cout
            << "thread_id: " << std::this_thread::get_id() << std::endl
            << "message: " << message->get_payload() << std::endl;
}
