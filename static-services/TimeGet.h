#pragma once

#include "AbstractService.h"

#include <string>

#include <json/value.h>

struct TimeGet : public AbstractService {
    void execute(const Json::Value&, Json::Value&) override;
};