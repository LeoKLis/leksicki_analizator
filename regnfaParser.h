#ifndef REGNFA_PARSER_H
#define REGNFA_PARSER_H

#include<string>
#include<iostream>
#include <vector>
#include <map>

#define EPSILON "$"


using namespace std;

class RegnfaParser {
private:
    vector<map<string, vector<int> >> stateTransitions;      //Indexed states, maps transitions to next states
    map<int, string> finalStates;        //for int index gives regex
    int n;
    int createState();
    int createState(string reg);
    void addTransition(int from, int to, string znak);
    void addTransition(int from, int to, char znak);

    void constuctNFA(int start, int end, string reg);
    static bool je_operator(string reg, int i);
public:
    RegnfaParser(){
        n=0;
        createState();
    };
    void parse(std::string regex, std::string action);
    void print();
    void finalPrint();
};


#endif /*REGNFA_PARSER_H*/
