#include <fstream>

#include <json.hpp>

#include "file_format.h"
#include "transition.h"

int main(int, char const *argv[]) {
    // read inputs into a json structure
    nlohmann::json inputJson = readInputs(argv[1]);
    // check the version and update as needed
    bool const success = applyAnyConversion(inputJson);
    if (!success) {
        return 1;
    }
    // finally do any simulation
    // simulate(foo);
}
