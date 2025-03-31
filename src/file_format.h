#ifndef FORMAT_H
#define FORMAT_H

#include <json.hpp>

nlohmann::json idfToJSON(std::string const & idf);
std::string jsonToIDF(nlohmann::json const & json);

#endif //FORMAT_H
