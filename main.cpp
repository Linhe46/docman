#include <fstream>
#include <iostream>
#include <vector>

#include "citation.h"
#include "utils.hpp"

#include "third_parties/nlohmann/json.hpp"
#include "third_parties/cpp-httplib/httplib.h"

std::vector<Citation *> loadCitations(const std::string &filename)
{
    // FIXME: load citations from file
    std::vector<Citation*>c;
    std::ifstream file{filename};
    nlohmann::json data=nlohmann::json::parse(file);
    for(auto& item:data["citations"]){
        auto id=item["id"].get<std::string>();
        auto type=item["type"].get<std::string>();
        Citation* cite;
        if(type=="book")
                cite=new Book(id,book,item["isbn"].get<std::string>());
        else if(type=="webpage")
                cite=new Book(id,webpage,item["url"].get<std::string>());
        else if(type=="article"){
            auto author=item["author"].get<std::string>();
            auto title=item["title"].get<std::string>();
            auto journal=item["journal"].get<std::string>();
            auto year=std::to_string(item["year"].get<int>());
            auto volume=item["volume"].get<std::string>();
            auto issue=item["issue"].get<std::string>();
            cite=new Article(id,article,author,title,journal,year,volume,issue);
        }
        c.push_back(cite);
    }
    return c;
}

int main(int argc, char **argv)
{
    // "docman", "-c", "citations.json", "input.txt"

    auto citations = loadCitations(argv[2]);
    std::vector<Citation *> printedCitations{};

    // FIXME: read all input to the string, and process citations in the input text
    // auto input = readFromFile(argv[3]);
    // ...

    std::ostream &output = std::cout;

    // output << input;  // print the paragraph first
    // output << "\nReferences:\n";

    for (auto c : printedCitations)
    {
        // FIXME: print citation
    }

    for (auto c : citations)
    {
        delete c;
    }
}
