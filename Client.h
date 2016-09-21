#pragma once

#include "NoCopy.h"

#include <websocketpp/server.hpp>

#include <boost/uuid/uuid.hpp>

class Server;

class Client : private NoCopy {
    friend class Server;

public:

    Client(boost::uuids::uuid connection_id, websocketpp::connection_hdl handle);
    virtual ~Client();

    bool is_authorized() const;

private:

    const std::string user_id;
    const boost::uuids::uuid connection_id;
    const websocketpp::connection_hdl handle;

    void on_connect();
    void on_disconnect();
};