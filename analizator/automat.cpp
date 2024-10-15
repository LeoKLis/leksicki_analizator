#include "automat.h"

#include <map>
#include <vector>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

bool Automat::isFinished(){

    if(done==true){
        done=false;
        return true;
    }

    return false;
}

/*
int NfaSimulator::createState(){
    map<string, vector<int>> mapa;
    (nfa.stateTransitions).push_back(mapa);
    return nfa.size()-1;
}
*/

void Automat::addTransition(int from, int to, string znak){

    map<string, vector<int>> stateMap = nfa.stateTransitions.at(from);

    if (stateMap.find(znak) != stateMap.end()) {
        ((nfa.stateTransitions.at(from)).at(znak)).push_back(to);
    } else {
        vector<int> v;
        v.push_back(to);
        (nfa.stateTransitions.at(from)).insert({ znak, v });
    }
}

void Automat::addTransition(int from, int to, char znak){
    string novi_znak = {znak};
    addTransition(from, to, novi_znak);
}

vector<int> Automat::transition(int state, char znak){
    vector<int> next_states;

    string novi_znak = {znak};

    return (nfa.stateTransitions.at(state)).at(novi_znak);
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

    if(new_current.size()==0)
        done=true;
    else
        currentStates=new_current;


}

vector<string> Automat::get_action(){

    vector<int> sorted_states;

    vector<int> for_removal; //uklanjanje stanja koja nisu zavrsna iz trenutacnih stanja prije sortiranja
    for(auto i:currentStates){
        if(nfa.acceptStatesMap.find(i)==nfa.acceptStatesMap.end())
          for_removal.push_back(i);
    }
    for(auto i:for_removal)
        currentStates.erase(i);


    for(auto i : currentStates)
        sorted_states.push_back(i);

    currentStates.clear();
    currentStates.insert(0);

    sort(sorted_states.begin(), sorted_states.end());



    if(sorted_states.size()==0){
        vector<string> prazno;
        return prazno;
    }


    return (nfa.acceptStatesMap).at(sorted_states.at(0));
}

