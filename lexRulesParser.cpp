#include "lexRulesParser.h"

#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

LexRules LexRulesParser::parse()
{
    LexRules lexRules;
    string line;
    while (getline(cin, line)) {
        parseLine(line, lexRules);
    }
    return lexRules;
}

// Takes input line, determines category for parsing and
// forwards it to the corresponding function
void LexRulesParser::parseLine(string line, LexRules& lexRules)
{
    if (line[0] == '{') {
        appendRegdefs(line, lexRules);
    }
    if (line.substr(0, 2) == "%X") {
        appendStates(line, lexRules);
    }
    if (line.substr(0, 2) == "%L") {
        appendLexUnits(line, lexRules);
    }
    if (line[0] == '<') {
        appendLexRules(line, lexRules);
    }
}

void LexRulesParser::appendRegdefs(string line, LexRules& lexRules)
{
    int emptyIndex = line.find(" ");
    string regdefName = line.substr(0, emptyIndex);
    string regdefDefinition = line.substr(emptyIndex + 1);
    if (isRegex(regdefDefinition)) {
        lexRules.regexMap.insert(make_pair(regdefName, regdefDefinition));
        return;
    }
    for (int i = 0; i < regdefDefinition.length(); i++) {
        if (regdefDefinition[i] == '{') {
            bool foundRegdef = false;
            int j;
            for (j = i + 1; j < regdefDefinition.length(); j++) {
                if (!isLetter(regdefDefinition[j]))
                    break;
                if (regdefDefinition[j] == '}') {
                    foundRegdef = true;
                    break;
                }
            }
            string regdef = regdefDefinition.substr(i, j - i + 1);
            if (lexRules.regexMap.count(regdef))
                regdefDefinition.replace(i, j - i + 1, '(' + lexRules.regexMap.at(regdef) + ')');
        }
    }
    lexRules.regexMap.insert(make_pair(regdefName, regdefDefinition));
}

void LexRulesParser::appendStates(string line, LexRules& lexRules)
{
    line = line.substr(line.find(" ") + 1);
    string state;
    while (line.find(" ") != string::npos) {
        state = line.substr(0, line.find(" "));
        lexRules.lexStates.push_back(state);
        line = line.substr(line.find(" ") + 1);
    }
    lexRules.lexStates.push_back(line);
}

void LexRulesParser::appendLexUnits(string line, LexRules& lexRules)
{
    line = line.substr(line.find(" ") + 1);
    string state;
    while (line.find(" ") != string::npos) {
        state = line.substr(0, line.find(" "));
        lexRules.lexUnits.push_back(state);
        line = line.substr(line.find(" ") + 1);
    }
    lexRules.lexUnits.push_back(line);
}

void LexRulesParser::appendLexRules(string line, LexRules& lexRules)
{
    int delimiterIndex = line.find('>');
    string stateName = line.substr(0, delimiterIndex + 1);
    string stateRegex = line.substr(delimiterIndex + 1);

    if (!isRegex(stateRegex)) {
        for (int i = 0; i < stateRegex.length(); i++) {
            if (stateRegex[i] == '{') {
                bool foundRegdef = false;
                int j;
                for (j = i + 1; j < stateRegex.length(); j++) {
                    if (!isLetter(stateRegex[j]))
                        break;
                    if (stateRegex[j] == '}') {
                        foundRegdef = true;
                        break;
                    }
                }
                string regdef = stateRegex.substr(i, j - i + 1);
                if (lexRules.regexMap.count(regdef))
                    stateRegex.replace(i, j - i + 1, '(' + lexRules.regexMap.at(regdef) + ')');
            }
        }
    }

    string rule;
    vector<string> rules;
    while (getline(cin, rule)) {
        if (rule == "{")
            continue;
        if (rule == "}")
            break;
        rules.push_back(rule);
    }

    lexRules.lexRuleMap[stateName].push_back({ stateRegex, rules });
}

// Checks if regular definition definition is actually just regular expression
bool LexRulesParser::isRegex(string regdefDef)
{
    return !regex_search(regdefDef, regex("\\{[a-zA-Z]+\\}"));
}

bool LexRulesParser::isLetter(char letter)
{
    return (letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z');
}