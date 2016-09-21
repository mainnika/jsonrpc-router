#include "Rpc.h"

Rpc::Rpc() : AbstractServer(this->connector, jsonrpc::JSONRPC_SERVER_V2) {
}

Rpc::~Rpc() {
}

