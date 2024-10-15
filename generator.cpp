// Kompajlirati sa "make"

// Generator funkcionalnost
// - cita leksicka pravila sa standardnog ulaza (a.exe < pravila.txt)
// - pretvara regularne definicije u regularne izraze (regdefParser.h)
// - generira .c ili .txt sa eps-NKA (nkaParser.h)

#include "regdefParser.h"
#include "regnfaParser.h"

#include "regdefParser.cpp"
#include "regnfaParser.cpp"

#include <iostream>
#include <map>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    RegdefParser rdp;

    string line;
    while (getline(cin, line)) {
        rdp.parseLine(line);
    }

    // ofstream nkaFile("analizator/nfa.txt");

    for(auto it = rdp.lexRuleMap.cbegin(); it != rdp.lexRuleMap.cend(); it++){
        NFA nfa = RegnfaParser::parse(it->first, it->second);
        // nkaFile << "\n" << it->first << "\n";

        // for(int i=0; i<nfa.stateTransitions.size(); i++){
        //     nkaFile << i << " ";
        //     for(auto it = nfa.stateTransitions[i].cbegin(); it != nfa.stateTransitions[i].cend(); it++){
        //         nkaFile << it->first << " ";
        //         for(auto se : it->second){
        //             nkaFile << se << " ";
        //         }
        //     }
        //     nkaFile << "\n";
        // }
        // nkaFile << "\n";
        // for(auto it = nfa.acceptStatesMap.cbegin(); it != nfa.acceptStatesMap.cend(); it++){
        //     nkaFile << it->first << " ";
        //     for(auto se : it->second){
        //         nkaFile << se << " ";
        //     }
        //     nkaFile << "\n";
        // }
    }

    // nkaFile.close();

    return 0;
}
