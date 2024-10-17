#include "nfaDeserializer.h"
#include "nfaSimulator.h"
#include "nfa.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    vector<NFA> nfaArray = NfaDeserializer::deserializeNfas("nfa_structure.txt");
    vector<string> lexUnits = NfaDeserializer::deserializeLexUnits("nfa_structure.txt");
    
    NfaSimulator nfasim(nfaArray);
    nfasim.loadFromStdin();
    nfasim.simulate();
    // nfasim.printTable();
    nfasim.printAsSource();
}