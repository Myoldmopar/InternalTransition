#ifndef FORMAT_H
#define FORMAT_H

#include <json.hpp>

nlohmann::json idfToJSON(std::string const & idf);
std::string jsonToIDF(nlohmann::json const & json);
nlohmann::json parseIDF(const std::string& idfText);
nlohmann::json parseEpJSON(std::string const & jsonText);
nlohmann::json readInputs(std::string const & fileToRead);

#endif //FORMAT_H
