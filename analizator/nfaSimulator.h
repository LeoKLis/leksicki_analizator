#ifndef NFA_SIMULATOR_H
#define NFA_SIMULATOR_H

#include "automat.h"

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

struct row {
    string uniformSymbol;
    int rowNumber; // to je broj retka u programu(row in program) rege
    string lexUnit;
};

class nfaSimulator {
private:
    vector<Automat> automati;
    map<string,int> nfa_names;
    int currentState;

    void doAction(vector<string>);
    int redak;
    int pocetak=0;
    int zavrsetak=0;
    int posljednji=0;

public:
    nfaSimulator(vector<Automat> nfaovi);
    void simulate()

    vector<row> finalTable;
};

#endif
