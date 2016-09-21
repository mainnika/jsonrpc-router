#pragma once

#include "Mqp.h"

#include <jsonrpccpp/server.h>

class Rpc : public jsonrpc::AbstractServer<Rpc> {
public:

    Rpc();
    virtual ~Rpc();

private:

    Mqp connector;

};