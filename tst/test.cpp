#include <gtest/gtest.h>
#include <json.hpp>

#include "file_format.h"
#include "transition.h"

TEST(TestTransition, IDFVersion251to252) {
    std::string const idfText = R"(
version,25.1;
coil:cooling:dx,coil,12.0;
    )";
    nlohmann::json json = parseIDF(idfText);
    bool const success = applyAnyConversion(json);
    ASSERT_TRUE(success);
    ASSERT_TRUE(json["coil:cooling:dx"].contains("schedule"));
    ASSERT_EQ("default", json["coil:cooling:dx"]["schedule"]);
    ASSERT_FLOAT_EQ(json["coil:cooling:dx"]["capacity"], 24.0);
}

TEST(TestTransition, EpJSONFileVersion251to252) {
    std::string const jsonText = R"(
{
  "version": "25.1",
  "coil:cooling:dx" : {
    "name": "My Coil", "capacity": 12.0
  }
}
    )";
    nlohmann::json json = parseEpJSON(jsonText);
    bool const success = applyAnyConversion(json);
    ASSERT_TRUE(success);
    ASSERT_TRUE(json["coil:cooling:dx"].contains("schedule"));
    ASSERT_EQ("default", json["coil:cooling:dx"]["schedule"]);
    ASSERT_FLOAT_EQ(json["coil:cooling:dx"]["capacity"], 24.0);
}

TEST(TestTransition, EpJSONTextVersion251to252) {
    nlohmann::json json = {
        {"version", "25.1"},
        {"coil:cooling:dx", {
                {"name", "My Coil"},
                {"capacity", 12.0}
        }},
    };
    bool const success = applyAnyConversion(json);
    ASSERT_TRUE(success);
    ASSERT_TRUE(json["coil:cooling:dx"].contains("schedule"));
    ASSERT_EQ("default", json["coil:cooling:dx"]["schedule"]);
    ASSERT_FLOAT_EQ(json["coil:cooling:dx"]["capacity"], 24.0);
}

TEST(TestTransition, EpJSONTextAlreadyVersion252) {
    nlohmann::json json = {
        {"version", "25.2"},
        {"coil:cooling:dx", {
                    {"name", "My Coil"},
                    {"capacity", 12.0},
                    {"schedule", "not_default"}
        }},
    };
    bool const success = applyAnyConversion(json);
    ASSERT_TRUE(success);
    ASSERT_TRUE(json["coil:cooling:dx"].contains("schedule"));
    std::string schedEntry = json["coil:cooling:dx"]["schedule"];
    ASSERT_EQ("not_default", schedEntry);
    ASSERT_FLOAT_EQ(json["coil:cooling:dx"]["capacity"], 12.0);
}

