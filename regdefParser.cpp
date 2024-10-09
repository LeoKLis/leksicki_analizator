#include "regdefParser.h"

// Takes input line, determines category for parsing and
// forwards it to the corresponding function
void RegdefParser::parseLine(string line)
{
    if (line[0] == '{') {
        appendRegdefs(line);
    }
    if (line.substr(0, 2) == "%X") {
        appendStates(line);
    }
    if (line.substr(0, 2) == "%L") {
        appendLexUnits(line);
    }
    if (line.substr(0, 2) == "<S") {
        appendLexRules(line);
    }
}

void RegdefParser::appendRegdefs(string line)
{
    int emptyIndex = line.find(" ");
    string regdefName = line.substr(0, emptyIndex);
    string regdefDefinition = line.substr(emptyIndex + 1);
    if (isRegex(regdefDefinition)) {
        regexMap.insert(make_pair(regdefName, regdefDefinition));
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
            if (regexMap.count(regdef))
                regdefDefinition.replace(i, j - i + 1, '(' + regexMap.at(regdef) + ')');
        }
    }
    regexMap.insert(make_pair(regdefName, regdefDefinition));
}

void RegdefParser::appendStates(string line)
{
    line = line.substr(line.find(" ") + 1);
    string state;
    while (line.find(" ") != string::npos) {
        state = line.substr(0, line.find(" "));
        states.push_back(state);
        line = line.substr(line.find(" ") + 1);
    }
    states.push_back(line);
}

void RegdefParser::appendLexUnits(string line)
{
    line = line.substr(line.find(" ") + 1);
    string state;
    while (line.find(" ") != string::npos) {
        state = line.substr(0, line.find(" "));
        lexUnits.push_back(state);
        line = line.substr(line.find(" ") + 1);
    }
    lexUnits.push_back(line);
}

void RegdefParser::appendLexRules(string line)
{
    int delimiterIndex = line.find('>');
    string stateName = line.substr(0, delimiterIndex + 1);
    string stateRegdef = line.substr(delimiterIndex + 1);

    if(!isRegex(stateRegdef)){
        for (int i = 0; i < stateRegdef.length(); i++) {
        if (stateRegdef[i] == '{') {
            bool foundRegdef = false;
            int j;
            for (j = i + 1; j < stateRegdef.length(); j++) {
                if (!isLetter(stateRegdef[j]))
                    break;
                if (stateRegdef[j] == '}') {
                    foundRegdef = true;
                    break;
                }
            }
            string regdef = stateRegdef.substr(i, j - i + 1);
            if (regexMap.count(regdef))
                stateRegdef.replace(i, j - i + 1, '(' + regexMap.at(regdef) + ')');
        }
    }
    }

    string rule;
    vector<string> rules;
    while(getline(cin, rule)){
        if(rule == "{") continue;
        if(rule == "}") break;
        rules.push_back(rule);
    }

    lexRuleMap.insert(make_pair(make_pair(stateName, stateRegdef), rules));
}

// Checks if regular definition definition is actually just regular expression
bool RegdefParser::isRegex(string regdefDef)
{
    return !regex_search(regdefDef, regex("\\{[a-zA-Z]+\\}"));
}

bool RegdefParser::isLetter(char letter)
{
    return (letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z');
}

void RegdefParser::printRegexMap()
{
    for (auto it = regexMap.cbegin(); it != regexMap.cend(); it++) {
        cout << it->first << " -> " << it->second << endl;
    }
}

void RegdefParser::printStates()
{
    for (auto it = states.begin(); it < states.end(); it++) {
        cout << *it << " ";
    }
    cout << "\n";
}

void RegdefParser::printLexicalUnits()
{
    for (auto it = lexUnits.begin(); it < lexUnits.end(); it++) {
        cout << *it << " ";
    }
    cout << "\n";
}

void RegdefParser::printLexicalRules(){
    cout << lexRuleMap.size() << "\n\n";
    for(auto it = lexRuleMap.cbegin(); it != lexRuleMap.cend(); it++){
        cout << it->first.second << " -> ";
        for(auto sec = it->second.begin(); sec < it->second.end(); sec++){
            cout << *sec << ", ";
        }
        cout << "\n";
    }
}