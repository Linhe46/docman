#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

#include "citation.h"
#include "utils.hpp"

#include "third_parties/nlohmann/json.hpp"

std::vector<Citation *> loadCitations(const std::string &filename)
{
    // FIXME: load citations from file
    std::vector<Citation*>c;
    std::ifstream file{filename};
    nlohmann::json data=nlohmann::json::parse(file);
    for(auto& item:data["citations"]){
        auto id=item["id"].get<std::string>();
        auto type=item["type"].get<std::string>();
        Citation* cite=nullptr;
        if(type=="book")
                cite=new Book(id,book,item["isbn"].get<std::string>());
        else if(type=="webpage")
                cite=new Webpage(id,webpage,item["url"].get<std::string>());
        else if(type=="article"){
            auto author=item["author"].get<std::string>();
            auto title=item["title"].get<std::string>();
            auto journal=item["journal"].get<std::string>();
            auto year=std::to_string(item["year"].get<int>());
            auto volume=std::to_string(item["volume"].get<int>());
            auto issue=std::to_string(item["issue"].get<int>());
            cite=new Article(id,article,author,title,journal,year,volume,issue);
        }
        c.push_back(cite);
    }
    return c;
}
std::string readFromFile(const std::string& filename){
    std::ifstream file(filename);
    std::string s;
    char x;
    while(file.get(x))
        s += x;
    return s;
}
void output_idx(std::vector<Citation*>&c,const std::string& input,const
std::vector<Citation *>& citations){
    std::vector<std::string>idxes;
    char x;
    std::string id;
    std::istringstream input_stream(input);
    bool flag=0;
    while(input_stream.get(x)){
        if(x=='['){
            flag=1;
            id="";
            continue;
        }
        if(x==']'){
            if(flag){
                flag=0;
                idxes.push_back(id);
            }
            else std::exit(1);//无匹配的左括号
            continue;
        }
        id+=x;
    }
    if(flag==1)
        std::exit(1);//无匹配的右括号
    std::sort(idxes.begin(),idxes.end());
    for(auto i:idxes)
        for(auto cite:citations)
            if(cite->id==i)
                c.push_back(cite);
}
int main(int argc, char **argv)
{
    // "docman", "-c", "citations.json", "input.txt"

    auto citations = loadCitations(argv[2]);
    std::vector<Citation *> printedCitations{};

    // FIXME: read all input to the string, and process citations in the input text
    // auto input = readFromFile(argv[3]);
    // ...
    auto input=readFromFile(argv[3]);
    output_idx(printedCitations,input,citations);

    std::ostream &output = std::cout;

    // output << input;  // print the paragraph first
    // output << "\nReferences:\n";
    output<<input<<"\n";
    output<<"\nReferences:\n";

    for (auto c : printedCitations)
    {
        // FIXME: print citation
        c->printCitation();
    }

    for (auto c : citations)
    {
        delete c;
    }
}
//./main -c source.json article.txt
//g++ main.cpp -o main -lws2_32