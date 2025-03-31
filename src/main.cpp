#include <iostream>

#include <json.hpp>

#include "transition.h"

int main() {
    nlohmann::json inputJson;
    inputJson["version"] = "25.1";
    if (inputJson["version"] != "25.2") {
        bool const success = convert251to252(inputJson);
        if (!success) {
            std::cerr << "Failed to convert input json" << std::endl;
            return 1;
        }
        std::cout << "Converted inputs from 25.1 to 25.2" << std::endl;
    }
    // simulate(foo);
}
