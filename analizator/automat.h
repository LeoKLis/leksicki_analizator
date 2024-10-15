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
    //int transition(int state, char znak);
    void epsilon();
public:
    Automat(){
        currentStates.insert(0); //prvo stanje je p0
        done=false;
    }
    NFA nfa;
    bool done;
    string get_name(){
        return nfa.state;
    }

    int createState(){
        map<string, vector<int>> mapa;
        (nfa.stateTransitions).push_back(mapa);
        return nfa.stateTransitions.size()-1;
    }

    vector<int> transition(int state, char znak);
    void addTransition(int from, int to, string znak);
    void addTransition(int from, int to, char znak);
    bool isFinished();
    set<int> epsilon(set<int>);
    void readChar(char letter);
    vector<string> get_action();


    //kreiranje toga



};

#endif
