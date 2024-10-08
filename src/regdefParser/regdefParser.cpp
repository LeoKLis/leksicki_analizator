#include "regdefParser.h"

RegdefParser::RegdefParser()
{
}

// Replaces regular definition with regular expression
// Example
// regdef - {hexZnamenka} {znamenka}|a|b|c|d|e|f
// regex - {znamenka} 0|1|2|3|4|5|6|7|8|9
// result - {hexZnamenka} (0|1|2|3|4|5|6|7|8|9)|a|b|c|d|e|f
void RegdefParser::parse(string regdef, string regex)
{
    int regexSpaceIndex = regex.find(" ");
    string regexName = regex.substr(0, regexSpaceIndex);
    string regexRaw = "(" + regex.substr(regexSpaceIndex + 1) + ")";

    for (int i = 0; i <= regdef.length() - regexName.length(); i++)
    {
        if (regdef.substr(i, regexName.length()) == regexName)
        {
            regdef.replace(i, regexName.length(), regexRaw);
        }
    }

    cout << regdef;
}

bool RegdefParser::isRegex(string regdef)
{
    int regdefSpaceIndex = regdef.find(" ");
    string regdefRaw = regdef.substr(regdefSpaceIndex + 1);

    cout << regdefRaw << endl;

    regex reg("\\{[a-zA-Z]+\\}");

    return !regex_search(regdefRaw, regex("\\{[a-zA-Z]+\\}"));
}