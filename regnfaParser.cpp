#include "regnfaParser.h"

int RegnfaParser::createState(){
    map<string, vector<int>> state;
    n=n+1;
    stateTransitions.push_back(state);
    return n-1;
}

int RegnfaParser::createState(string reg){
    int state = createState();
    finalStates.insert({state, reg});
    return state;
}

bool RegnfaParser::je_operator(string reg, int i){
    int br=0;
    while(i-1>0 && reg[i-1]=='\\'){
        br++;
        i=i-1;
    }
return (br%2==0);
}

void RegnfaParser::addTransition(int from, int to, string znak){
    map<string, vector<int>> stateMap = stateTransitions.at(from);

    if(stateMap.find(znak)!=stateMap.end()){
        ((stateTransitions.at(from)).at(znak)).push_back(to);
    }
    else{
        vector<int> v;
        v.push_back(to);
        (stateTransitions.at(from)).insert({znak, v});
    }
}

void RegnfaParser::addTransition(int from, int to, char znak){
    string novi_znak{znak};
    addTransition(from, to, novi_znak);
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

            choice=reg.substr(last_grouped, i-last_grouped);
            last_grouped=i+1;
            izbori.push_back(choice);
        }
    }
    izbori.push_back(reg.substr(last_grouped, reg.length() - last_grouped)); // grupiranje ostatka


    //cout<<"izbori slozeni" << izbori.size()<<endl;

    if(izbori.size()>1){
        for(int i=0; i<izbori.size(); i++){
            int state=createState();
            //stateTransitions.at(state).insert({EPSILON, state});//epsilon transition
            addTransition(start, state, EPSILON);
            constuctNFA(state, end, izbori[i]);
        }
    }
    else{
        bool prefiksirano=false;
        int zadnje_stanje = start;
        for(int i=0; i<reg.length(); i++){
            int a,b;
            if(prefiksirano==true){ ///slucaj1
                prefiksirano=false;
                string prijelazni_znak=string{reg[i]};
                if(prijelazni_znak.compare("t"))
                    prijelazni_znak='\t';
                else if(prijelazni_znak.compare("n"))
                    prijelazni_znak='\n';
                else if(prijelazni_znak.compare("_"))
                    prijelazni_znak=' ';
                else
                    prijelazni_znak=reg[i];
                //prijelazni_znak[prijelazni_znak.length()]='\0';
                a=createState();
                b=createState();
                addTransition(a, b, prijelazni_znak);
            }
            else{ ///slucaj2
                if(reg[i]=='\\'){
                    prefiksirano=true;
                    continue;
                }
                if(reg[i]!='('){ ///slucaj 2a
                    a=createState();
                    b=createState();
                    if(reg[i]=='$')
                        addTransition(a, b, EPSILON);
                        //stateTransitions.at(a).insert({EPSILON, b});
                    else
                        addTransition(a, b, reg[i]);
                        //stateTransitions.at(a).insert({reg[i], b});
                   }
                else{ ///slucaj 2b

                    int trazim=1;
                    int j=i+1;
                    while(1%2 ==1){
                        if(reg[j]=='(') trazim=trazim+1;
                        else if(reg[j]==')') trazim=trazim-1;
                        if(trazim==0){
                            //j=k;
                            break;
                        }
                        j++;
                    }

                    a=createState();
                    b=createState();
                    //cout<<"tu su problemi"<<endl;
                    constuctNFA(a,b, reg.substr(i+1, j-1-i));
                    //cout<<"ipak nisu";
                    i=j;
                }

            }

            //provjera ponavljanja
            if(i+1<reg.length() && reg[i+1]=='*'){
                int x=a;
                int y=b;
                a=createState();
                b=createState();

                addTransition(a, x, EPSILON);
                addTransition(y, b, EPSILON);
                addTransition(a, b, EPSILON);
                addTransition(y, x, EPSILON);

                i=i+1;
                //stateTransitions.at(a).insert({EPSILON, x});
                //stateTransitions.at(y).insert({EPSILON, b});
                //stateTransitions.at(a).insert({EPSILON, b});
                //stateTransitions.at(y).insert({EPSILON, x});

            }
            //stateTransitions.at(zadnje_stanje).insert({EPSILON, a});
            addTransition(zadnje_stanje, a, EPSILON);
            zadnje_stanje=b;
        }
        //stateTransitions.at(zadnje_stanje).insert({EPSILON, end});
        addTransition(zadnje_stanje, end, EPSILON);
    }
}

void RegnfaParser::parse(string regex, string action){
    int startingState = createState();
    int endingState = createState(action);

    addTransition(0,startingState, EPSILON);

    constuctNFA(startingState, endingState, regex);
}

void RegnfaParser::print(){

    for(int i=0; i<stateTransitions.size(); i++){
        map<string, vector<int>> mapa = stateTransitions.at(i);

        cout<<"Stanje "<<i<<endl;
        for(auto vek : mapa){
            cout<<"\tZnak "<<vek.first<<":\t";
            for(int j=0; j<vek.second.size()-1; j++){
                cout<<vek.second.at(j)<<", ";
            }
            cout<<vek.second.at(vek.second.size()-1)<<endl;
        }

    }

}

void RegnfaParser::finalPrint(){
    cout<<endl;
    for(auto i : finalStates){
        cout<<i.first<<" ---> "<<i.second<<endl;
    }
}
