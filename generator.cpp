// Generator funkcionalnost
// - cita leksicka pravila sa standardnog ulaza (a.exe < pravila.txt)
// - pretvara regularne definicije u regularne izraze (regdefParser.h)
// - generira .c ili .txt sa eps-NKA (nkaParser.h)

#include "lexRulesParser.h"
#include "regexToNFAParser.h"

#include <vector>
using namespace std;

int main()
{
    LexRules lexRules = LexRulesParser::parse();
    vector<NFA> nfaArr = RegexToNFAParser::parse(lexRules.lexStates, lexRules.lexRuleMap);
    RegexToNFAParser::serialize("analizator/nfa_structure.txt", lexRules.lexUnits, nfaArr);
    return 0;
}
