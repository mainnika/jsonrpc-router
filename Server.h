#pragma once

#include <thread>

#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls.hpp>

typedef websocketpp::server<websocketpp::config::asio> WebsocketServer;
typedef websocketpp::connection_hdl Connection;

class Server : public WebsocketServer {
public:
    Server();
    virtual ~Server();

    std::unique_ptr<std::thread> run_thread();

private:
    static void on_message(Server *self, Connection handle, Server::message_ptr message);

};

