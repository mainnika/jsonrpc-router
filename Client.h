#pragma once

#include <websocketpp/server.hpp>

#include <boost/uuid/uuid.hpp>

class Server;

class Client {
    friend class Server;

public:

    Client(boost::uuids::uuid connection_id, websocketpp::connection_hdl handle);
    virtual ~Client();

private:

    const boost::uuids::uuid connection_id;
    const websocketpp::connection_hdl handle;

    void on_message(std::string &message);
    void on_connect();
    void on_disconnect();
};