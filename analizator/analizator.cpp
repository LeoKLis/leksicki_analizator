// #include "nfaSimulator.h"
#include "nfaDeserializer.h"
#include <vector>

int main()
{
    vector<NFA> nfaArray = NfaDeserializer::deserializeNfas("nfa_structure.txt");
    vector<string> lexUnits = NfaDeserializer::deserializeLexUnits("nfa_structure.txt");
}