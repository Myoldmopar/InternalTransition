#include <iostream>

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

bool applyAnyConversion(nlohmann::json &json) {
    if (json["version"] == "25.1") {
        bool const success = convert251to252(json);
        if (!success) {
            std::cerr << "Failed to convert input json" << std::endl;
            return false;
        }
        // std::cout << "Converted inputs from 25.1 to 25.2" << std::endl;
    }
    return true;
}
