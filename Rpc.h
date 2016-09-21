#pragma once

#include "NoCopy.h"

#include <jsonrpccpp/server.h>

class Server;

class Rpc : public jsonrpc::AbstractServer<Server>, private NoCopy {
public:

    Rpc(Server *server);
    virtual ~Rpc();

private:

    Mqp mqp;
};