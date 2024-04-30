#pragma once
#ifndef CITATION_H
#define CITATION_H

#include <string>

#include "third_parties/cpp-httplib/httplib.h"
#include "third_parties/nlohmann/json.hpp"
#include "utils.hpp"

enum Type
{
    book,
    webpage,
    article
};
httplib::Client client{API_ENDPOINT};

class Citation{
    Type type;
public:
    std::string id;
    Citation() {}
    Citation(std::string id_, Type type_) : id(id_), type(type_) {}
    virtual void get()=0;
    virtual void printCitation(std::ostream&)=0;
};

class Book : public Citation{
    std::string isbn;
    std::string author,title,publisher,year;
public:
    Book(std::string id_, Type type_, std::string isbn_) : Citation(id_, type_), isbn(isbn_) {get();}
    void get() override{
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
    void printCitation(std::ostream& out) override{
        out<<'['<<id<<"] book: "<<author<<", "
        <<title<<", "<<publisher<<", "<<year<<"\n";
    }
};
class Webpage : public Citation{
    std::string url;
    std::string title;
public:
    Webpage(std::string id_, Type type_, std::string url_) : Citation(id_, type_), url(url_) {get();}
    void get() override{
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
    void printCitation(std::ostream& out) override{
        out<<'['<<id<<"] webpage: "<<title<<". Available at "
        <<url<<"\n";
    }
};
class Article : public Citation{
    std::string author,title,journal,year,volume,issue;
public:
    Article(std::string id_,Type type_,std::string author_,std::string title_,
    std::string journal_,std::string year_,std::string volume_,std::string issue_):
    Citation(id_,type_),author(author_),title(title_),journal(journal_),year(year_),
    volume(volume_),issue(issue_){get();}
    void get()override{
        return;
    }
    void printCitation(std::ostream& out) override{
        out<<'['<<id<<"] article: "<<author<<", "
        <<title<<", "<<journal<<", "<<year<<", "<<volume<<
        ", "<<issue<<"\n";
    }
};
#endif