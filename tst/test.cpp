#include <gtest/gtest.h>
#include <json.hpp>

#include "file_format.h"
#include "transition.h"

TEST(TestTransition, IDFVersion251to252) {
    std::string const pretendIDF = R"(
      {
        "version": "25.1",
        "coil:cooling:dx": {
          "name": "My Coil",
          "capacity": 12.0
        }
      }
    )";
    nlohmann::json json = idfToJSON(pretendIDF);
    bool const success = convert251to252(json);
    ASSERT_TRUE(success);
    ASSERT_TRUE(json["coil:cooling:dx"].contains("schedule"));
    ASSERT_FLOAT_EQ(json["coil:cooling:dx"]["capacity"], 24.0);
}

TEST(TestTransition, EpJSONVersion251to252) {
    nlohmann::json json = {
        {"version", "25.1"},
        {"coil:cooling:dx", {
                {"name", "My Coil"},
                {"capacity", 12.0}
        }},
    };
    json["version"] = "25.1";
    bool const success = convert251to252(json);
    ASSERT_TRUE(success);
    ASSERT_TRUE(json["coil:cooling:dx"].contains("schedule"));
    ASSERT_FLOAT_EQ(json["coil:cooling:dx"]["capacity"], 24.0);
}
