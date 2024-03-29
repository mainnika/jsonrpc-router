#include "Server.h"
#include "Client.h"

#include <iostream>
#include <chrono>
#include <functional>

#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

Server::Server() : jsonrpc::AbstractServerConnector(), websocketpp::server<websocketpp::config::asio>(),
rpc(this) {

    this->init_asio();
    this->set_open_handler(std::bind(&Server::on_connect, this, std::placeholders::_1));
    this->set_close_handler(std::bind<void(&)(Server*, websocketpp::connection_hdl)>(Server::on_disconnect, this, std::placeholders::_1));
}

Server::~Server() {
}

Server::thread_t Server::run_thread() {

    return std::make_unique<std::thread>([this]() -> void {

        std::cout << "thread #" << std::this_thread::get_id() << " started" << std::endl;

        this->run();
    });
}

void Server::on_message(Server* self, Client *client, Server::message_ptr message_ptr) {

    auto message = message_ptr->get_payload();

    std::cout
            << "thread_id: " << std::this_thread::get_id() << std::endl
            << "message: " << message << std::endl;

    self->OnRequest(message, client);
}

void Server::on_connect(Server* self, websocketpp::connection_hdl handle) {

    std::cout
            << "thread_id: " << std::this_thread::get_id() << std::endl
            << "new_client: " << std::endl;

    static thread_local boost::uuids::random_generator uuid_gen;

    Server::clients_t::accessor accessor;
    auto uuid = uuid_gen();

    if (self->clients.insert(accessor, uuid)) {

        auto client = new Client(uuid, handle);
        auto connection = self->get_con_from_hdl(handle);

        std::cout << "connection was successfully established: " << uuid << std::endl;

        accessor->second = client;

        connection->set_message_handler(std::bind(&Server::on_message, self, client, std::placeholders::_2));
        connection->set_close_handler(std::bind<void(&)(Server*, Client*)>(Server::on_disconnect, self, client));

        client->on_connect();

        return;
    }

    std::cout << "connection wasn't established: " << uuid << std::endl;

    self->close(handle, websocketpp::close::status::try_again_later, "unknown error");
}

void Server::on_disconnect(Server* self, websocketpp::connection_hdl handle) {

    std::cout
            << "thread_id: " << std::this_thread::get_id() << std::endl
            << "disconnect_unknown: " << std::endl;
}

void Server::on_disconnect(Server* self, Client *client) {

    std::cout
            << "thread_id: " << std::this_thread::get_id() << std::endl
            << "disconnect_client: " << client->connection_id << std::endl;

    Server::authorized_clients_t::accessor authorized_accessor;
    if (client->is_authorized() && self->authorized_clients.find(authorized_accessor, client->user_id)) {
        self->authorized_clients.erase(authorized_accessor);
    }

    Server::clients_t::accessor accessor;
    if (self->clients.find(accessor, client->connection_id)) {
        self->clients.erase(accessor);
    }

    delete client;
}

bool Server::SendResponse(const std::string& response, void* data) {

    try {
        Client *client = static_cast<Client*> (data);
        auto connection = this->get_con_from_hdl(client->handle);

        connection->send(response);
        return true;

    } catch (...) {

        return false;
    }
}

bool Server::StartListening() {

    return false;
}

bool Server::StopListening() {

    return false;
}
