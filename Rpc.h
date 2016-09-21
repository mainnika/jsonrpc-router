#pragma once

#include "Mqp.h"
#include "NoCopy.h"
#include "static-services/AbstractService.h"

#include <string>
#include <memory>

#include <jsonrpccpp/common/procedure.h>
#include <jsonrpccpp/server/iprocedureinvokationhandler.h>
#include <jsonrpccpp/server/iclientconnectionhandler.h>

#include <tbb/concurrent_hash_map.h>

class Server;
class AbstractService;

class Rpc : public jsonrpc::IProcedureInvokationHandler, private NoCopy {
public:

    Rpc(Server *server);
    virtual ~Rpc();

    void add_method(const jsonrpc::Procedure &proc, std::unique_ptr<AbstractService> handler);

private:
    typedef tbb::concurrent_hash_map<std::string, std::unique_ptr<AbstractService>> methods_t;
    typedef jsonrpc::IProtocolHandler handler_t;

    Mqp mqp;
    Server *server;
    methods_t methods;
    handler_t *handler;

    void HandleMethodCall(jsonrpc::Procedure& proc, const Json::Value& input, Json::Value& output) override;
    void HandleNotificationCall(jsonrpc::Procedure& proc, const Json::Value& input) override;
};