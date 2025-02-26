#include "demo_v1_User.h"
#include <nlohmann/json.hpp>

using namespace demo::v1;

using nlohmann_json = nlohmann::json;
class JSONParser {
    public:
        // TestCase class to hold the Input (now as a string) and Output
        class TestCase {
        public:
            std::string input; // Now input is a simple string
            std::string output;
    
            // Define the deserialization from JSON
            NLOHMANN_DEFINE_TYPE_INTRUSIVE(TestCase, input, output)
        };
    
        // TestCases class to hold the array of TestCase
        class TestCases {
        public:
    
            std::string type;
            std::string version;
            std::vector<TestCase> test_cases;
    
            // Define the deserialization from JSON
            NLOHMANN_DEFINE_TYPE_INTRUSIVE(TestCases, type, version, test_cases)
        };
    
        // Function to parse and print JSON
        static void parseAndPrint(const std::string& json_data) {
            // Parse the JSON string into the TestCases object
            TestCases test_cases = nlohmann_json::parse(json_data);
    
            std::cout << "test_cases.type : " << test_cases.type << std::endl;
            std::cout << "test_cases.version : " << test_cases.version << std::endl;
    
            // Output the parsed data
            for (const auto& test_case : test_cases.test_cases) {
                std::cout << "Input: " << test_case.input << std::endl;
                std::cout << "Output: " << test_case.output << std::endl;
            }
        }
    };

void parseIO()
{
    //const std::string rawJson = R"({"Age": 20, "Name": "colin"})";

    const std::string rawJson = R"(
    {
      "type" : "std",
      "version" : "std_json_v1",
      "test_cases": [
        {
          "input": "3 5",
          "output": "8"
        },
        {
          "input": "2 2",
          "output": "4"
        },
        {
          "input": "5 1",
          "output": "6"
        }
      ]
    })";

    JSONParser::parseAndPrint(rawJson);
}


// Add definition of your processing function here

void User::login(const HttpRequestPtr &req,
    std::function<void (const HttpResponsePtr &)> &&callback,
    std::string &&userId,
    const std::string &password)
{
    LOG_DEBUG<<"User "<<userId<<" login";
    //Authentication algorithm, read database, verify, identify, etc...
    //...

    parseIO();
    Json::Value ret;
    ret["result"]="ok";
    ret["token"]=drogon::utils::getUuid();
    auto resp=HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
}
void User::getInfo(const HttpRequestPtr &req,
      std::function<void (const HttpResponsePtr &)> &&callback,
      std::string userId,
      const std::string &token) const
{
    LOG_DEBUG<<"User "<<userId<<" get his information";

    //Verify the validity of the token, etc.
    //Read the database or cache to get user information
    Json::Value ret;
    ret["result"]="ok";
    ret["user_name"]="Jack";
    ret["user_id"]=userId;
    ret["gender"]=1;
    auto resp=HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
}


void User::helloGet(const HttpRequestPtr &req,
    std::function<void (const HttpResponsePtr &)> &&callback) const
{
    LOG_DEBUG<<"HelloGet Called";

    //Verify the validity of the token, etc.
    //Read the database or cache to get user information
    Json::Value ret;
    ret["result"]="ok";
    ret["myMessage"]="Hello";
       
    auto resp=HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
}
