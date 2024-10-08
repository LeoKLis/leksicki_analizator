#include "regdefParser.h"
#include<string>
#include<iostream>

using namespace std;

int main(){
    string regdef = "{hexZnamenka} {znamenka}|a|b|c|d|e|f|A|B|C|D|E|F";
    string regex = "{znamenka} 0|1|2|3|4|5|6|7|8|9";

    RegdefParser rdp;
    // rdp.parse(regdef, regex);

    cout << rdp.isRegex(regdef) << endl;
    cout << rdp.isRegex(regex);
}