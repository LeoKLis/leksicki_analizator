#include "nfaSimulator.h"

#include "automat.h"

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

nfaSimulator::nfaSimulator(vector<Automat> nfaovi){
    automati = nfaovi;
    currentState=0;
    redak=1;
    int pocetak=0;
    int zavrsetak=0; //iterator koji iterira
    int posljednji=0; //

    for(int i=0; i<nfaovi.size(); i++)
        nfa_names.insert({automati.nfa.state, i});

}

void nfaSimulator::doAction(vector<string> action, string niz){
    for(auto act : action){

        if(act == "NOVI_REDAK")
            redak=redak+1;
        else if(act == "-")
            continue;
        else if(act.substr(0,act.find(" "))=="VRATI_SE"){
            int broj = stoi(act.substr(act.find(" ")+1));
            posljednji=pocetak+broj-1;
        }
        else if(act.substr(0,act.find(" ")) == "UDJI_U_STANJE"){
            string newState = act.substr(act.find(" ")+1);
            currentState = nfa_names.at(newState);
            automati[currentState].restart();
        }
        else{
            row WOR;
            WOR.lexUnit=act;
            WOR.rowNumber=redak;
            WOR.uniformSymbol=niz;
            finalTable.push_back(WOR);
        }
    }
}


void nfaSimulator::simulate(){

    string input;

    pocetak=0;
    zavrsetak=0;
    posljednji=0;
    vector<string> izraz;

    while(getline(cin,input)){ //nema za procitat

        for(auto znak : input){

            switch automati[currentState].isFinished(){
            case 0:
                automati[currentState].readChar(znak);
                zavrsetak=zavrsetak+1;
                break;
            case 1:
                izraz=automati[currentState].get_action();
                posljednji=zavrsetak;
                zavrsetak=zavrsetak+1;
                automati[currentState].readChar(znak);
                break;
            case 2:
                if(izraz.empty()){
                    pocetak=pocetak+1;
                    zavrsetak=pocetak;
                }
                else{
                    string niz = substr(niz, pocetak, posljednji-pocetak);
                    doAction(izraz); //TREBA DODATI NIZ SIMBOLA KOJI SE KORISTE
                    izraz.clear();
                    pocetak=posljednji+1;
                    zavrsetak=pocetak;
                }
                break;
            }
        }
    }

}
