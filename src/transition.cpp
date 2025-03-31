#include <json.hpp>

#include "transition.h"

bool convert251to252(nlohmann::json & json) {
    if (json.contains("bad_key")) {
        return false;
    }
    if (json.contains("coil:cooling:dx")) {
        double const current_capacity = json["coil:cooling:dx"]["capacity"];
        double const new_capacity = current_capacity * 2;
        json["coil:cooling:dx"]["capacity"] = new_capacity;
        json["coil:cooling:dx"]["schedule"] = "default";
    }
    json["version"] = "25.2";
    return true;
}
