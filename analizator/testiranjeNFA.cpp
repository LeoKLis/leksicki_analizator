#include "nfaSimulator.h"
#include "nfaSimulator.cpp"

#include <iostream>

using namespace std;

int main(){

    NfaSimulator nfa;


    nfa.createState();
    nfa.createState();
    nfa.createState();
    nfa.createState();
    nfa.createState();

    nfa.addTransition(0,4, "z");
    nfa.addTransition(0,1,"$");
    nfa.addTransition(1,2,"$");
    nfa.addTransition(2,3, "$");

    vector<string> aaaa;

    string akcijski="opasno";
    aaaa.push_back(akcijski);
    akcijski="nije opasno";
    aaaa.push_back(akcijski);

    nfa.nfa.acceptStatesMap.insert({4, aaaa});


    while(1){
        if(!nfa.isFinished()){
            char a;
            cin>>a;
            nfa.readChar(a);
        }
        else{
            vector<string> akcija=nfa.get_action();

            for(auto i:akcija)
                cout<<endl<<"evo ga: "<<i;
            return 0;
        }

    }


    return 0;
}
