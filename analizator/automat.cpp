#include "automat.h"

#include <map>
#include <vector>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int Automat::isFinished(){ //0 - nema finalnih, ali ima stanja; 1 - ima i finalnih i mozda obicnih; 2  - nema stanja

    if(currentStates.size()==0){
        return 2;
    }
    if(currentStates.size()>0){
        for(auto i:currentStates){
            if(nfa.acceptStatesMap.find(i)!=nfa.acceptStatesMap.end())
                return 1;
        }
    }

    return 0;
}



set<int> Automat::epsilon(set<int> current){

    set<int> next_states;

    if(current.size()==0)
        return next_states;


    for(auto i: current){

        map<string, vector<int>> mapa = nfa.stateTransitions.at(i);
        string epsiloncek={'$'};
        if(mapa.count(epsiloncek)){
            for(auto j: transition(i, '$'))
                next_states.insert(j);
        }
    }

    set<int> more_next_states = epsilon(next_states);


   for(auto i: more_next_states)
        next_states.insert(i);

    return next_states;
}

void Automat::readChar(char letter){
    string znak = {letter};

    //Epsilon okruzenje
    set<int> temp;
    for(auto i : epsilon(currentStates))
        temp.insert(i);
    for(auto i:temp)
        currentStates.insert(i);


    //ozbiljan dio sada

    set<int> new_current;

    for(auto i : currentStates){
        if((nfa.stateTransitions.at(i)).count(znak)){
            for(auto i: transition(i, letter))
                new_current.insert(i);
        }
    }

    currentStates=new_current;
}

void Automat::restart(){

    currentStates.clear();
    currentStates.insert(0);

}

vector<string> Automat::get_action(){

    vector<int> sorted_states;


    vector<int> copy_current;

    for(auto i : currentStates){
        if(nfa.acceptStatesMap.count(i))
            copy_current.push_back(i);
    }

    sort(copy_current.begin(), copy_current.end());

    if(copy_current.size()==0)
        return sorted_states;
    return copy_current.at(0);
}

