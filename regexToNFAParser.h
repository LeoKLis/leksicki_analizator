#ifndef REGNFA_PARSER_H
#define REGNFA_PARSER_H

#define EPSILON "$"
#define NFA_STRUCTURE vector<map<string, vector<int>>>
#define LEX_RULES_STRUCTURE vector<pair<string, vector<string>>>

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// Structure that stores epsilon-NFA transitions and accepting states
// @param stateTransitions contains epsilon-NFA transitions stored in vector
// @param acceptStatesMap contains accept states and their action stored in map
struct NFA {
    string state;
    NFA_STRUCTURE stateTransitions;
    map<int, vector<string>> acceptStatesMap;
};

class RegexToNFAParser {
private:
    static void constructNFA(NFA_STRUCTURE* stateTransitions, int start, int end, string reg, int* stateCount);
    static int createState(NFA_STRUCTURE* stateTransitions, int* stateCount);
    static void addTransition(NFA_STRUCTURE* stateTransitions, int from, int to, string znak);

    static bool isOperator(string reg, int i);

public:
    // Parses lexical states and lexical rules to epsilon NFA
    // @param lexStates array of lexical states
    // @param lexRuleMap map of lexical rules for each state
    // @returns array of epsilon NFAs for each state
    static vector<NFA> parse(vector<string> lexStates, map<string, vector<pair<string, vector<string>>>> lexRuleMap);
    static NFA parseRegex(string stateName, LEX_RULES_STRUCTURE rules);
    static void serialize(string fileName, vector<string> lexUnits, vector<NFA> nfaArr);
    static void printNFA(vector<NFA> nfas);
};

#endif
