#include <fstream>
#include <iostream>
#include <vector>

#include "citation.h"
#include "utils.hpp"

#include "cpp-httplib/httplib.h"
int main()
{
    auto url = "www.pytorch.org";
    httplib::Client client{API_ENDPOINT};
    auto result = client.Get("/title/" + encodeUriComponent(url));
    std::cout << result->body << std::endl;

    auto isbn = "9787530214732";
    auto result_ = client.Get("/isbn/" + encodeUriComponent(isbn));
    std::cout << result_->body << std::endl;
}