#include <fstream>
#include <iostream>
#include <vector>
#include "third_parties/nlohmann/json.hpp"

#include "citation.h"
#include "utils.hpp"

#include "cpp-httplib/httplib.h"
int main()
{
    auto url = "www.pytorch.org";
    httplib::Client client{API_ENDPOINT};
    auto result = client.Get("/title/" + encodeUriComponent(url));
    std::cout << result->body << std::endl;

    nlohmann::json data1 = nlohmann::json::parse(result->body);
    std::string title = data1["title"].get<std::string>();
    std::cout << title << std::endl;

    auto isbn = "9787530214732";
    auto result_ = client.Get("/isbn/" + encodeUriComponent(isbn));
    std::cout << result_->body << std::endl;

    nlohmann::json data2 = nlohmann::json::parse(result_->body);
    auto author_ = data2["author"].get<std::string>();
    auto title_ = data2["title"].get<std::string>();
    auto publisher_ = data2["publisher"].get<std::string>();
    auto year_ = data2["year"].get<std::string>();
    std::cout << author_ << ' ' << title_ << ' ' << publisher_ << ' ' << year_ << std::endl;
}
// g++ mytest.cpp -o mytest -lws2_32