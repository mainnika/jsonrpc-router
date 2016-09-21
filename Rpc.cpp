#include "Rpc.h"

#include "Server.h"

Rpc::Rpc(Server *server) :
jsonrpc::AbstractServer<Server>(*server, jsonrpc::JSONRPC_SERVER_V2) {
}

Rpc::~Rpc() {
}

