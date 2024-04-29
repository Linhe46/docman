#pragma once
#ifndef CITATION_H
#define CITATION_H

#include <string>

enum Type
{
    book,
    webpage,
    article
};

class Citation
{
    std::string id;
    Type type;

public:
    Citation() {}
    Citation(std::string id_, Type type_) : id(id_), type(type_) {}
};
class Book : public Citation{
    std::string isbn;
public:
    Book(std::string id_, Type type_, std::string isbn_) : Citation(id_, type_), isbn(isbn_) {}
};
class Webpage : public Citation{
    std::string url;
public:
    Webpage(std::string id_, Type type_, std::string url_) : Citation(id_, type_), url(url_) {}
};
class Article : public Citation{
    std::string author,title,journal,year,volume,issue;
public:
    Article(std::string id_,Type type_,std::string author_,std::string title_,
    std::string journal_,std::string year_,std::string volume_,std::string issue_):
    Citation(id_,type_),author(author_),title(title_),journal(journal_),year(year_),
    volume(volume_),issue(issue_){}
};
#endif