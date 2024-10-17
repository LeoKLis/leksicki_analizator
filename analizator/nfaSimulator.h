#ifndef NFA_SIMULATOR_H
#define NFA_SIMULATOR_H

#include "nfa.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class NfaSimulator {
private:
    struct Row {
        string uniformSymbol;
        int rowNumber; // to je broj retka u programu(row in program) rege
        string lexUnit;
    };
    vector<Row> finalTable;
    
    vector<NFA> automati;
    map<string, int> nfaNames;
    int currentState;
    int redak;
    int pocetak;
    int zavrsetak;
    int posljednji;

    // Applies an action given to it
    // 1. "NOVI_REDAK" - adds +1 to redak
    // 2. "-" - ignores input and continues
    // 3. "VRATI_SE" - returns to nth number, stores it and continues from there
    // 4. "UDJI_U_STANJE" - goes into state that was given to it
    // 5. DEFAULT - appends uniform symbol, redak, lexUnit to row
    void doAction(vector<string> action, string niz);

public:
    string codeString;
    NfaSimulator(vector<NFA> nfaovi);
    void loadFromStdin();
    void simulate();
    void printTable();
};

#endif
