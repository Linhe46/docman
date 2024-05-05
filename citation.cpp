#include "citation.h"
#include "third_parties/nlohmann/json.hpp"

httplib::Client client{API_ENDPOINT};

void Book::get(){
        auto result=client.Get("/isbn/"+encodeUriComponent(isbn));
        if(result&&result->status==httplib::OK_200){
            nlohmann::json data=nlohmann::json::parse(result->body);
            author = data["author"].get<std::string>();
            title = data["title"].get<std::string>();
            publisher = data["publisher"].get<std::string>();
            year = data["year"].get<std::string>();
        }
        else{
            auto err=result.error();
            std::cerr<<"HTTP error: "<<httplib::to_string(err)<<std::endl;
        }
    }
void Book::printCitation(std::ostream& out){
        out<<'['<<id<<"] book: "<<author<<", "
        <<title<<", "<<publisher<<", "<<year<<"\n";
    }

void Webpage::get(){
        auto result=client.Get("/title/"+encodeUriComponent(url));
        if(result&&result->status==httplib::OK_200){
            nlohmann::json data=nlohmann::json::parse(result->body);
            title = data["title"].get<std::string>();
        }
        else{
            auto err=result.error();
            std::cerr<<"HTTP error: "<<httplib::to_string(err)<<std::endl;
        }
    }
void Webpage::printCitation(std::ostream& out){
        out<<'['<<id<<"] webpage: "<<title<<". Available at "
        <<url<<"\n";
    }

void Article::get(){
        return;
    }
void Article::printCitation(std::ostream& out){
        out<<'['<<id<<"] article: "<<author<<", "
        <<title<<", "<<journal<<", "<<year<<", "<<volume<<
        ", "<<issue<<"\n";
    }