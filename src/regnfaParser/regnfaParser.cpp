#include "regnfaParser.h"

int RegnfaParser::createState(){
    map<string, int> state;
    n=n+1;
    stateTransitions.push_back(state);
    return n-1;
}

int RegnfaParser::createState(string reg){
    int state = createState();
    finalStates.insert({state, reg});
    return state;
}

void RegnaParser::RegnaParser(){
    n=0;
    createState();//p0
}

bool RegnfaParser::je_operator(string reg, int i){
    int br=0;
    while(i-1>0 && reg[i-1]=='\\'){
        br++;
        i=i-1;
    }
return (br%2==0);
}

void RegnfaParser::constuctNFA(int start, int end, string reg){
    vector<string> izbori;
    int last_grouped=0;

    int brackets=0;

    for(int i=0; i<reg.length(); i++){
        if(reg[i]=='(' && je_operator(reg,i))
            brackets=brackets+1;
        else if(reg[i]==')' && je_operator(reg,i))
            brackets=brackets-1;
        else if(brackets==0 && reg[i]=='|' && je_operator(reg, i)){
            string choice;


            //size_t len = reg.copy(choice, i-last_grouped,last_grouped);

            choice=reg.substr(last_grouped, i-last_grouped);

            //choice[len]='\0';
            last_grouped=i+1;
            izbori.push_back(choice);
        }
    }

    if(izbori.size()>0){
        for(int i=0; i<izbori.size(); i++){
            int state=createState();
            stateTransitions.at(state).insert({EPSILON, state});//epsilon transition
            constuctNFA(state, end, izbori[i]);
        }
    }
    else{
        bool prefiksirano=false;
        int zadnje_stanje = start;
        for(int i=0; i<reg.length(); i++){
            int a,b;
            if(prefiksirano==true){ //slucaj1
                prefiksirano=false;
                string prijelazni_znak;
                if(prijelazni_znak.compare('t'))
                    prijelazni_znak='\t';
                else if(prijelazni_znak.compare('n'))
                    prijelazni_znak='\n';
                else if(prijelazni_znak.compare('_'))
                    prijelazni_znak=' ';
                else
                    prijelazni_znak=reg[i];
                prijelazni_znak[prijelazni_znak.length()]='\0';
                a=createState();
                b=createState();
                stateTransitions.at(a).insert({prijelazni_znak, b});
            }
            else{ //slucaj2
                if(reg[i]=='\\'){
                    prefiksirano=true;
                    continue;
                }
                if(reg[i]!='('){ //slucaj 2a
                    a=createState();
                    b=createState();
                    if(reg[i]=='$')
                        stateTransitions.at(a).insert({EPSILON, b});
                    else
                        stateTransitions.at(a).insert({reg[i], b});
                   }
                else{ //slucaj 2b
                    int j;

                    int trazim=1;
                    int k=i;
                    while(1%2 ==1){
                        if(reg[k]=='(') trazim=trazim+1;
                        else if(reg[k]==')') trazim=trazim-1;
                        if(trazim==0){
                            j=k;
                            break;
                        }
                        k++;
                    }

                    a=createState();
                    b=createState();
                    constuctNFA()
                    i=j;
                }


            }

            //provjera ponavljanja
            if(i+1<reg.length() && reg[i+1]=='*'){
                int x=a;
                int y=b;
                a=createState();
                b=createState();
                stateTransitions.at(a).insert({EPSILON, x});
                stateTransitions.at(y).insert({EPSILON, b});
                stateTransitions.at(a).insert({EPSILON, b});
                stateTransitions.at(y).insert({EPSILON, x});

            }
            stateTransitions.at(zadnje_stanje).insert({EPSILON, a});
            zadnje_stanje=b;
        }
        stateTransitions.at(zadnje_stanje).insert({EPSILON, end});
    }



}

void RegnfaParser::parse(std::string regex, std::string regex action){
    int startingState = createState();
    int endingState = createState(action);
    constuctNFA(startingState, endingState, regex);
}


