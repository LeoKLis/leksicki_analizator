// Kompajlirati 

// Generator funkcionalnost
// - cita leksicka pravila sa standardnog ulaza (a.exe < pravila.txt)
// - pretvara regularne definicije u regularne izraze (regdefParser.h)
// - generira .c ili .txt sa eps-NKA (nkaParser.h)

#include "regdefParser.h"

#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{
    RegdefParser rdp;

    string line;
    while(getline(cin, line)){
        rdp.parseLine(line);
    }

    rdp.printRegexMap();
    // rdp.printStates();
    // rdp.printLexicalUnits();
    // rdp.printLexicalRules();

    return 0;
}