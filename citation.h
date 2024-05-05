#pragma once
#ifndef CITATION_H
#define CITATION_H

#include <string>
#include "third_parties/cpp-httplib/httplib.h"
#include "utils.hpp"

enum Type
{
    book,
    webpage,
    article
};
extern httplib::Client client;

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
    void get() override;
    void printCitation(std::ostream& out) override;
};

class Webpage : public Citation{
    std::string url;
    std::string title;
public:
    Webpage(std::string id_, Type type_, std::string url_) : Citation(id_, type_), url(url_) {get();}
    void get() override;
    void printCitation(std::ostream& out) override;
};

class Article : public Citation{
    std::string author,title,journal,year,volume,issue;
public:
    Article(std::string id_,Type type_,std::string author_,std::string title_,
    std::string journal_,std::string year_,std::string volume_,std::string issue_):
    Citation(id_,type_),author(author_),title(title_),journal(journal_),year(year_),
    volume(volume_),issue(issue_){get();}
    void get()override;
    void printCitation(std::ostream& out) override;
};
#endif