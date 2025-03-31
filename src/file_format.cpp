#include "file_format.h"

nlohmann::json idfToJSON(std::string const & idf) {
  return nlohmann::json::parse(idf);;
}

std::string jsonToIDF(nlohmann::json const & json) {
  return json.dump(2);
}
