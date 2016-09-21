#include "Client.h"

#include <iostream>

#include <boost/uuid/uuid_io.hpp>

Client::Client(boost::uuids::uuid connection_id, websocketpp::connection_hdl handle) :
connection_id(connection_id), handle(handle) {
}

Client::~Client() {
}

bool Client::is_authorized() const {
    return !this->user_id.empty();
}

void Client::on_connect() {

    std::cout
            << "client_id: " << this->connection_id << std::endl
            << "connected: " << std::endl;
}

void Client::on_disconnect() {

    std::cout
            << "client_id: " << this->connection_id << std::endl
            << "disconnected: " << std::endl;
}