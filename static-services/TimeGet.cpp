#include "TimeGet.h"

#include <chrono>

void TimeGet::execute(const Json::Value&, Json::Value& result) {
    result = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
}
