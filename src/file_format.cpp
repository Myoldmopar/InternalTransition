#include <fstream>

#include "file_format.h"

#include <iostream>

nlohmann::json parseIDF(const std::string& idfText) {
  std::string content = idfText;  // non-const copy

  // Remove newlines and extra spaces (optional)
  std::erase(content, '\n');
  std::erase(content, '\r');

  std::stringstream ss(content);
  std::string objectStr;

  // this is hardwired in a goofy demo way
  nlohmann::json json;

  while (std::getline(ss, objectStr, ';')) { // Split objects by semicolon
    if (objectStr.empty()) continue; // Skip empty entries

    std::stringstream objStream(objectStr);
    std::string field;
    std::vector<std::string> fields;

    while (std::getline(objStream, field, ',')) { // Split fields by comma
      fields.push_back(field);
    }

    if (fields.size() == 1) {
      std::string singleField = fields[0];
      if (std::ranges::all_of(singleField, [](unsigned char c) { return std::isspace(c); })) {
        break;
      }
    }
    if (!fields.empty()) {
      std::string const objectName = fields[0];
      if (objectName == "version") {
        json["version"] = fields[1];
      } else if (objectName == "coil:cooling:dx") {
        json["coil:cooling:dx"] = {{"name", fields[1]}, {"capacity", std::stod(fields[2])}};
      } else {
        std::cerr << "Unknown object name: " << objectName << std::endl;
      }
    }
  }

  return json;
}

nlohmann::json parseEpJSON(std::string const & jsonText) {
  return nlohmann::json::parse(jsonText);
}

nlohmann::json readInputs(std::string const & fileToRead) {
  std::string const ext = fileToRead.substr(fileToRead.find_last_of('.') + 1);
  std::ifstream f(fileToRead);
  std::stringstream buffer;
  buffer << f.rdbuf();
  std::string inputText = buffer.str();
  if (ext == ".epjson") {
    return parseEpJSON(inputText);
  } // .idf
  return parseIDF(inputText);
}

nlohmann::json idfToJSON(std::string const & idf) {
  return nlohmann::json::parse(idf);;
}

std::string jsonToIDF(nlohmann::json const & json) {
  return json.dump(2);
}
