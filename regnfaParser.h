#ifndef REGNFA_PARSER_H
#define REGNFA_PARSER_H

#include <iostream>
#include <map>
#include <string>
#include <vector>

#define EPSILON '$'
#define NFA_STRUCTURE vector<map<char, vector<int>>>
#define LEX_RULES_STRUCTURE vector<pair<string, vector<string>>>

using namespace std;

// Structure that stores epsilon-NFA transitions and accepting states
// @param stateTransitions contains epsilon-NFA transitions stored in vector
// @param acceptStatesMap contains accept states and their action stored in map
struct NFA {
    NFA_STRUCTURE stateTransitions;
    map<int, vector<string>> acceptStatesMap;
};

class RegnfaParser {
private:
    static int createState(NFA_STRUCTURE *stateTransitions, int *stateCount);
    static void addTransition(NFA_STRUCTURE *stateTransitions, int from, int to, char znak);
    static void constructNFA(NFA_STRUCTURE *stateTransitions, int start, int end, string reg, int *stateCount);
    static bool isOperator(string reg, int i);
    static NFA_STRUCTURE addNFA(NFA_STRUCTURE *stateTransitions, std::string regex, int *stateCount);

public:
    static NFA parse(LEX_RULES_STRUCTURE rules);
    static void printNFA(NFA_STRUCTURE stateTransitions);
    static void printAcceptStates(map<int, vector<string>> acceptStatesMap);
};

#endif /*REGNFA_PARSER_H*/
