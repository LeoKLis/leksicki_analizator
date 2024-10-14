#ifndef NFA_SIMULATOR_H
#define NFA_SIMULATOR_H

#include<string>
#include<map>
#include<vector>

#define NFA_STRUCTURE vector<map<string, vector<int>>>

using namespace std;

struct NFA {
    string state;
    NFA_STRUCTURE stateTransitions;
    map<int, vector<string>> acceptStatesMap;
};

class NfaSimulator {
private:
    vector<int> currentStates;
public:
    NFA nfa;
    bool isFinished();
    void readChar(char letter);
};

#endif