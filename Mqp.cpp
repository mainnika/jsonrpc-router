#include "Mqp.h"

Mqp::Mqp() : jsonrpc::AbstractServerConnector() {
}

Mqp::~Mqp() {
}

bool Mqp::SendResponse(const std::string& response, void* data) {
    return false;
}

bool Mqp::StartListening() {
    return false;
}

bool Mqp::StopListening() {
    return false;
}
