#pragma once

#include "Rpc.h"
#include "helpers.h"

#include <thread>
#include <memory>
#include <string>

#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls.hpp>

#include <tbb/concurrent_hash_map.h>

class Client;

class Server : public websocketpp::server<websocketpp::config::asio> {
public:
    typedef std::unique_ptr<std::thread> thread_t;

    Server();
    virtual ~Server();

    thread_t run_thread();

private:
    typedef tbb::concurrent_hash_map<boost::uuids::uuid, std::shared_ptr<Client>> clients_t;
    typedef tbb::concurrent_hash_map<std::string, std::shared_ptr<Client>> authorized_clients_t;

    Rpc rpc;
    clients_t clients;
    authorized_clients_t authorized_clients;

    static void on_message(Server *self, Client *client, Server::message_ptr message);
    static void on_connect(Server *self, websocketpp::connection_hdl handle);
    static void on_disconnect(Server *self, websocketpp::connection_hdl handle);
    static void on_disconnect(Server *self, Client *client);
};

