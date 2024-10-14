#ifndef REGNFA_PARSER_H
#define REGNFA_PARSER_H

#include <iostream>
#include <map>
#include <string>
#include <vector>

#define EPSILON "$"
#define NFA_STRUCTURE vector<map<string, vector<int>>>
#define LEX_RULES_STRUCTURE vector<pair<string, vector<string>>>

using namespace std;

// Structure that stores epsilon-NFA transitions and accepting states
// @param stateTransitions contains epsilon-NFA transitions stored in vector
// @param acceptStatesMap contains accept states and their action stored in map
struct NFA {
    string state;
    NFA_STRUCTURE stateTransitions;
    map<int, vector<string>> acceptStatesMap;
};

class RegnfaParser {
private:
    static int createState(NFA_STRUCTURE *stateTransitions, int *stateCount);
    static void addTransition(NFA_STRUCTURE *stateTransitions, int from, int to, string znak);
    static void constructNFA(NFA_STRUCTURE *stateTransitions, int start, int end, string reg, int *stateCount);
    static bool isOperator(string reg, int i);

public:
    static NFA parse(string state, LEX_RULES_STRUCTURE rules);
    static void printNFA(NFA_STRUCTURE stateTransitions);
    static void printAcceptStates(map<int, vector<string>> acceptStatesMap);
};

#endif /*REGNFA_PARSER_H*/
