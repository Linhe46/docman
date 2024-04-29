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
    Type type;
};
class Citation_web
{
    std::string s;
};
class Article : public Citation
{
};
#endif