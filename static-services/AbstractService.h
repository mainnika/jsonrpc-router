#pragma once

#include <json/value.h>

struct AbstractService {
    virtual void execute(const Json::Value &, Json::Value &) = 0;
};