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
    if(data["citations"].is_null())
        std::exit(1);
    for(auto& item:data["citations"]){
        if(item["id"].is_null()||!item["id"].is_string())std::exit(1);
        auto id=item["id"].get<std::string>();
        if(item["type"].is_null()||!item["type"].is_string())std::exit(1);
        auto type=item["type"].get<std::string>();

        Citation* cite=nullptr;
        if(type=="book"){
                if(item["isbn"].is_null()||!item["isbn"].is_string()) std::exit(1);
                cite=new Book(id,book,item["isbn"].get<std::string>());
                }
        else if(type=="webpage"){
                if(item["url"].is_null()||!item["url"].is_string()) std::exit(1);
                cite=new Webpage(id,webpage,item["url"].get<std::string>());
                }
        else if(type=="article"){
            if(item["author"].is_null()||!item["author"].is_string())std::exit(1);
            auto author=item["author"].get<std::string>();

            if(item["title"].is_null()||!item["title"].is_string())std::exit(1);
            auto title=item["title"].get<std::string>();

            if(item["journal"].is_null()||!item["journal"].is_string())std::exit(1);
            auto journal=item["journal"].get<std::string>();

            if(item["year"].is_null()||!item["year"].is_number_integer())std::exit(1);
            auto year=std::to_string(item["year"].get<int>());

            if(item["volume"].is_null()||!item["volume"].is_number_integer())std::exit(1);
            auto volume=std::to_string(item["volume"].get<int>());

            if(item["issue"].is_null()||!item["issue"].is_number_integer())std::exit(1);
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
            if(flag) std::exit(1);//左括号未闭合
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
    for(auto i:idxes){
        bool searched=0;
        for(auto cite:citations){
            if(cite->id==i){
                if(find(c.begin(),c.end(),cite)==c.end())
                    c.push_back(cite);
                searched=1;
                break;}
        }
        if(!searched)
            std::exit(1);
    }
}
int main(int argc, char **argv)
{
    // "docman", "-c", "citations.json", "input.txt"
    std::string citations_path,input_path,input,output_path;
    bool std_cout_flag=0;
    if(argc==4){
        citations_path=argv[2];
        input_path=argv[3];
        std_cout_flag=1;
    }
    else if(argc==6){
        input_path=argv[5];
        if(std::string(argv[1])=="-c"&&std::string(argv[3])=="-o"){
            citations_path=argv[2];
            output_path=argv[4];
        }
        else if(std::string(argv[1])=="-o"&&std::string(argv[3])=="-c"){
            citations_path=argv[4];
            output_path=argv[2];
        }
        else std::exit(1);
    }

    if(input_path=="-")
        {   char c;
            input="";
            while(std::cin.get(c)){
                input+=c;
        }
        input.pop_back();
        }
    else input=readFromFile(input_path);
    auto citations = loadCitations(citations_path);
    std::vector<Citation *> printedCitations{};

    // FIXME: read all input to the string, and process citations in the input text
    // auto input = readFromFile(argv[3]);
    // ...
    
    output_idx(printedCitations,input,citations);

    std::ofstream outFile;
    if(!std_cout_flag) outFile.open(output_path);
    std::ostream &output = std_cout_flag?std::cout:outFile;

    // output << input;  // print the paragraph first
    // output << "\nReferences:\n";
    output<<input<<"\n";
    output<<"\n";
    output<<"References:\n";

    for (auto c : printedCitations)
    {
        // FIXME: print citation
        c->printCitation(output);
    }

    for (auto c : citations)
    {
        delete c;
    }
}
//./main -c source.json article.txt
//g++ main.cpp -o main -lws2_32
//./docman -c source.json article.txt

