#ifndef AUTOMAT_H
#define AUTOMAT_H

#include<string>
#include<map>
#include<vector>
#include <set>

#define NFA_STRUCTURE vector<map<string, vector<int>>>

using namespace std;

struct NFA {
    string state;
    NFA_STRUCTURE stateTransitions;
    map<int, vector<string>> acceptStatesMap;
};

class Automat {
private:
    set<int> currentStates;
    set<int> epsilon(set<int>);
    vector<int> transition(int state, char znak);
public:
    Automat(){
        currentStates.insert(0); //prvo stanje je p0
    }
    NFA nfa;
    bool done;

    int isFinished();
    void readChar(char letter);
    vector<string> get_action();

    void restart();



};

#endif
