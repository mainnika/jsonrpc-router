#pragma once

#include "Mqp.h"
#include "NoCopy.h"
#include "static-services/AbstractService.h"

#include <string>

#include <jsonrpccpp/server.h>

#include <tbb/concurrent_hash_map.h>

class Server;
class AbstractService;

class Rpc : public jsonrpc::AbstractServer<Rpc>, private NoCopy {
public:

    Rpc(Server *server);
    virtual ~Rpc();

private:
    typedef tbb::concurrent_hash_map<std::string, AbstractService*> methods_t;

    Mqp mqp;
    methods_t methods;

    void HandleMethodCall(jsonrpc::Procedure& proc, const Json::Value& input, Json::Value& output) override;
    void HandleNotificationCall(jsonrpc::Procedure& proc, const Json::Value& input) override;

    void dummy(const Json::Value& input, Json::Value& output);
};