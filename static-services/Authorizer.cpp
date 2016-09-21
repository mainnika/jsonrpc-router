#include "Authorizer.h"

void Authorizer::execute(const Json::Value&, Json::Value& result) {
    result = "AUTHORIZED";
}
