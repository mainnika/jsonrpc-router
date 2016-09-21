#include "Rpc.h"
#include "Server.h"

#include "static-services/Authorizer.h"
#include "static-services/TimeGet.h"

#include <functional>

#include <jsonrpccpp/server/requesthandlerfactory.h>

Rpc::Rpc(Server *server) :
server(server), handler(jsonrpc::RequestHandlerFactory::createProtocolHandler(jsonrpc::JSONRPC_SERVER_V2, *this)) {

    this->server->SetHandler(this->handler);

    this->add_method(jsonrpc::Procedure("AuthRequest", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_OBJECT, NULL), std::make_unique<Authorizer>());
    this->add_method(jsonrpc::Procedure("TimeGet", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_INTEGER, NULL), std::make_unique<TimeGet>());
}

Rpc::~Rpc() {
}

void Rpc::add_method(const jsonrpc::Procedure &proc, std::unique_ptr<AbstractService> handler) {

    auto name = proc.GetProcedureName();
    Rpc::methods_t::accessor accessor;

    if (this->methods.insert(accessor, name)) {
        accessor->second = std::move(handler);
        this->handler->AddProcedure(proc);
    }
}

void Rpc::HandleMethodCall(jsonrpc::Procedure& proc, const Json::Value& input, Json::Value& output) {

    auto name = proc.GetProcedureName();
    Rpc::methods_t::accessor accessor;

    if (this->methods.find(accessor, name)) {
        accessor->second->execute(input, output);
    }
}

void Rpc::HandleNotificationCall(jsonrpc::Procedure& proc, const Json::Value& input) {

}