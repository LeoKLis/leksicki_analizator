// Parser regularnih definicija funkcionalnost
// - pretvara regularne definicije u regularne izraze
// - sprema takve regularne izraze u mapu (map<str, str> regexMap)
// - sprema stanja u polje (vector<string> states)
// - sprema leksicke jedinke u polje (vector<string> lexUnits)
// - sprema leksicka pravila u mapu (map<pair<string, string>, vector<string>> lexRuleMap)

#ifndef REGDEF_PARSER_H
#define REGDEF_PARSER_H

#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

using namespace std;

#define RULES_STRUCTURE vector<pair<string, vector<string>>>

class RegdefParser {
private:
    bool isRegex(string regdef);
    bool isLetter(char letter);

    void appendRegdefs(string line);
    void appendStates(string line);
    void appendLexUnits(string line);
    void appendLexRules(string line);

public:
    map<string, string> regexMap;
    vector<string> states;
    vector<string> lexUnits;
    map<string, RULES_STRUCTURE> lexRuleMap;

    void parseLine(string line);

    void printRegexMap();
    void printStates();
    void printLexicalUnits();
    void printLexicalRules();
};

#endif /*REGDEF_PARSER_H*/