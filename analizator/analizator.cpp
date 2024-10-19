#include "nfa.h"
#include "nfaDeserializer.h"
#include "nfaSimulator.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    vector<NFA> nfaArray = NfaDeserializer::deserializeNfas("nfa_structure.txt");
    NfaSimulator nfasim(nfaArray);
    nfasim.loadFromStdin();
    nfasim.simulate();
    nfasim.printTable();
}