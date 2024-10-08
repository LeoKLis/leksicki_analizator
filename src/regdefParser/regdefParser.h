#ifndef REGDEF_PARSER_H
#define REGDEF_PARSER_H

#include <string>
#include <map>
#include <iostream>
#include <regex>

using namespace std;

class RegdefParser
{
private:
    map<string, string> regexMap;
public:
    RegdefParser();

    void parse(string regdef, string regex);

    bool isRegex(string regdef);

};

#endif /*REGDEF_PARSER_H*/