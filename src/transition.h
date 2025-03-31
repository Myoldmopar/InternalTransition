#ifndef TRANSITION_H
#define TRANSITION_H

#include <json.hpp>

bool convert251to252(nlohmann::json &json);
bool applyAnyConversion(nlohmann::json &json);

#endif //TRANSITION_H
