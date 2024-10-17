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

// Structure that contains rules for building regular expressions,
// lexical states, lexical units and NFAs
// @param regexMap stores regexes
// @param lexStates stores lexical states
// @param lexUnits stores lexical units
// @param lexRuleMap stores lexical rules as map so that every lexical state has its own transitions
struct LexRules {
    map<string, string> regexMap;
    vector<string> lexStates;
    vector<string> lexUnits;
    map<string, RULES_STRUCTURE> lexRuleMap;
};

// Reads lexical rules and parses them to the appropriate structures
// so that they can be processed further by RegexToNFAParser
class LexRulesParser {
private:
    static void parseLine(string line, LexRules& lexRules);

    static void appendRegdefs(string line, LexRules& lexRules);
    static void appendStates(string line, LexRules& lexRules);
    static void appendLexUnits(string line, LexRules& lexRules);
    static void appendLexRules(string line, LexRules& lexRules);

    static bool isRegex(string regdef);
    static bool isLetter(char letter);

public:
    static LexRules parse();
};

#endif /*REGDEF_PARSER_H*/