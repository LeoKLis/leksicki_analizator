#ifndef NFA_DESERIALIZER_H
#define NFA_DESERIALIZER_H

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#define NFA_STRUCTURE vector<map<string, vector<int>>>

using namespace std;

struct NFA {
    string state;
    NFA_STRUCTURE stateTransitions;
    map<int, vector<string>> acceptStatesMap;
};

class NfaDeserializer {
private:
    static string readChar(string& line);

public:
    static vector<NFA> deserializeNfas(string filePath);
    static vector<string> deserializeLexUnits(string filePath);

    static void printAcceptStates(vector<NFA> nfas);
    static void printNfas(vector<NFA> nfas);
};

#endif