#ifndef NFA_DESERIALIZER_H
#define NFA_DESERIALIZER_H

#include "nfa.h"
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

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