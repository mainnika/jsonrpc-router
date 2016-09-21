#include "Rpc.h"
#include "Server.h"

#include "static-services/Authorizer.h"

#include <functional>

#include <jsonrpccpp/common/procedure.h>

Rpc::Rpc(Server *server) :
jsonrpc::AbstractServer<Rpc>(*server, jsonrpc::JSONRPC_SERVER_V2),
methods({
    {"AuthRequest", new Authorizer()},
}
) {

    //    TODO: UGLY
    this->bindAndAddMethod(jsonrpc::Procedure("AuthRequest", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_STRING, NULL), &Rpc::dummy);
}

Rpc::~Rpc() {
}

void Rpc::HandleMethodCall(jsonrpc::Procedure& proc, const Json::Value& input, Json::Value& output) {
    auto name = proc.GetProcedureName();

    Rpc::methods_t::accessor accessor;

    if (this->methods.find(accessor, name)) {
        accessor->second->execute(input, output);
        return;
    }
}

void Rpc::HandleNotificationCall(jsonrpc::Procedure& proc, const Json::Value& input) {

}

void Rpc::dummy(const Json::Value& input, Json::Value& output) {

}
