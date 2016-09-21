#pragma once

#include <jsonrpccpp/server/abstractserverconnector.h>

class Mqp : public jsonrpc::AbstractServerConnector {
public:

    Mqp();
    virtual ~Mqp();

private:

    bool SendResponse(const std::string& response, void* data) override;
    bool StartListening() override;
    bool StopListening() override;
};
