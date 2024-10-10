#ifndef REGNFA_PARSER_H
#define REGNFA_PARSER_H

#include<string>
#include<iostream>
#include <vector>
#include <map>

#define EPSILON "$"

class RegnfaParser {
private:
    vector<map<string, int>> stateTransitions;      //Indexed states, maps transitions to next states
    map<int, string> finalStates;        //for int index gives regex
    int n;
    RegnfaParser();
    static int createState();
    static int createState(string reg);
    static void constuctNFA(int start, int end, string reg);
    static bool je_operator(string reg, int i);
public:
    static void parse(std::string regex, std::string action);
};


#endif /*REGNFA_PARSER_H*/
