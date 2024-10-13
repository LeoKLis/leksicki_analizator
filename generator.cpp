// Kompajlirati sa "make"

// Generator funkcionalnost
// - cita leksicka pravila sa standardnog ulaza (a.exe < pravila.txt)
// - pretvara regularne definicije u regularne izraze (regdefParser.h)
// - generira .c ili .txt sa eps-NKA (nkaParser.h)

#include "regdefParser.h"
#include "regnfaParser.h"

#include <iostream>
#include <map>
#include <string>


using namespace std;

int main()
{
    RegdefParser rdp;

    string line;
    while (getline(cin, line)) {
        rdp.parseLine(line);
    }

    NFA nfa = RegnfaParser::parse(rdp.lexRuleMap["<S_komentar>"]);
    RegnfaParser::printNFA(nfa.stateTransitions);
    RegnfaParser::printAcceptStates(nfa.acceptStatesMap);

    return 0;
}