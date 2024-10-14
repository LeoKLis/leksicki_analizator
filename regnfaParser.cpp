#include "regnfaParser.h"

int RegnfaParser::createState(NFA_STRUCTURE *stateTransitions, int *stateCount)
{
    map<string, vector<int>> state;
    stateTransitions->push_back(state);
    return (*stateCount)++;
}

bool RegnfaParser::isOperator(string reg, int i)
{
    int br = 0;
    while (i - 1 > 0 && reg[i - 1] == '\\') {
        br++;
        i = i - 1;
    }
    return (br % 2 == 0);
}

void RegnfaParser::addTransition(NFA_STRUCTURE *stateTransitions, int from, int to, string znak)
{
    map<string, vector<int>> stateMap = stateTransitions->at(from);

    if (stateMap.find(znak) != stateMap.end()) {
        ((stateTransitions->at(from)).at(znak)).push_back(to);
    } else {
        vector<int> v;
        v.push_back(to);
        (stateTransitions->at(from)).insert({ znak, v });
    }
}

void RegnfaParser::constructNFA(NFA_STRUCTURE *stateTransitions, int startState, int endState, string regex, int *stateCount)
{
    vector<string> izbori;
    int last_grouped = 0;
    int brackets = 0;
    for (int i = 0; i < regex.length(); i++) {
        if (regex[i] == '(' && isOperator(regex, i))
            brackets = brackets + 1;
        else if (regex[i] == ')' && isOperator(regex, i))
            brackets = brackets - 1;
        else if (brackets == 0 && regex[i] == '|' && isOperator(regex, i)) {
            string choice;
            choice = regex.substr(last_grouped, i - last_grouped);
            izbori.push_back(choice);
            last_grouped = i + 1;
        }
    }
    izbori.push_back(regex.substr(last_grouped)); // grupiranje ostatka

    if (izbori.size() > 1) {
        for (int i = 0; i < izbori.size(); i++) {
            int state = createState(stateTransitions, stateCount);
            addTransition(stateTransitions, startState, state, EPSILON);
            constructNFA(stateTransitions, state, endState, izbori[i], stateCount);
        }
    } else {
        bool prefiksirano = false;
        int zadnje_stanje = startState;
        for (int i = 0; i < regex.length(); i++) {
            int a, b;
            /// slucaj1 (prefiksirani znak)
            if (prefiksirano == true) {
                prefiksirano = false;
                string prijelazni_znak;
                // if (regex[i] == 't')
                //     prijelazni_znak = "\\t";
                // else if (regex[i] == 'n')
                //     prijelazni_znak = "\\n";
                // else if (regex[i] == '_')
                //     prijelazni_znak = "\\_";
                // else
                    prijelazni_znak = "\\" + string{regex[i]};
                a = createState(stateTransitions, stateCount);
                b = createState(stateTransitions, stateCount);
                addTransition(stateTransitions, a, b, prijelazni_znak);
            } else { /// slucaj2
                if (regex[i] == '\\') {
                    prefiksirano = true;
                    continue;
                }
                /// slucaj 2a (ako je znak samo)
                if (regex[i] != '(') {
                    a = createState(stateTransitions, stateCount);
                    b = createState(stateTransitions, stateCount);
                    if (regex[i] == '$')
                        addTransition(stateTransitions, a, b, EPSILON);
                    else
                        addTransition(stateTransitions, a, b, string{regex[i]});
                } else { /// slucaj 2b (ako je naso izraz u zagradi, rekurzivno nastavlja algoritam)
                    int trazim = 1;
                    int j = i + 1;
                    while (1 % 2 == 1) {
                        if (regex[j] == '(')
                            trazim = trazim + 1;
                        else if (regex[j] == ')')
                            trazim = trazim - 1;
                        if (trazim == 0) {
                            break;
                        }
                        j++;
                    }

                    a = createState(stateTransitions, stateCount);
                    b = createState(stateTransitions, stateCount);
                    // cout<<"tu su problemi"<<endl; (ostaje u kodu hahaha!!!)
                    constructNFA(stateTransitions, a, b, regex.substr(i + 1, j - i - 1), stateCount);
                    // cout<<"ipak nisu";
                    i = j;
                }
            }

            // provjera ponavljanja (kleenov operator)
            if (i + 1 < regex.length() && regex[i + 1] == '*') {
                int x = a;
                int y = b;
                a = createState(stateTransitions, stateCount);
                b = createState(stateTransitions, stateCount);

                addTransition(stateTransitions, a, x, EPSILON);
                addTransition(stateTransitions, y, b, EPSILON);
                addTransition(stateTransitions, a, b, EPSILON);
                addTransition(stateTransitions, y, x, EPSILON);

                i = i + 1;
            }
            addTransition(stateTransitions, zadnje_stanje, a, EPSILON);
            zadnje_stanje = b;
        }
        addTransition(stateTransitions, zadnje_stanje, endState, EPSILON);
    }
}

NFA RegnfaParser::parse(string state, LEX_RULES_STRUCTURE rules){
    NFA_STRUCTURE stateTransitions;
    map<int, vector<string>> acceptStatesMap;
    int stateCount = 0;
    int initialState = createState(&stateTransitions, &stateCount);

    for(auto it : rules){
        int startState = createState(&stateTransitions, &stateCount);
        int endState = createState(&stateTransitions, &stateCount);
        addTransition(&stateTransitions, initialState, startState, EPSILON);
        acceptStatesMap[endState] = it.second;
        constructNFA(&stateTransitions, startState, endState, it.first, &stateCount);
    }

    return NFA{state, stateTransitions, acceptStatesMap};
}

void RegnfaParser::printNFA(NFA_STRUCTURE stateTransitions)
{
    for (int i = 0; i < stateTransitions.size(); i++) {
        map<string, vector<int>> mapa = stateTransitions.at(i);
        cout << "Stanje " << i << endl;
        for (auto vek : mapa) {
            cout << "\tZnak " << vek.first << ": ";
            for (int j = 0; j < vek.second.size() - 1; j++) {
                cout << vek.second.at(j) << ", ";
            }
            cout << vek.second.at(vek.second.size() - 1) << endl;
        }
    }
}

void RegnfaParser::printAcceptStates(map<int, vector<string>> acceptStatesMap){
    for(auto it = acceptStatesMap.cbegin(); it != acceptStatesMap.cend(); it++){
        cout << "Stanje: " << it->first << endl;
        for(auto sc : it->second){
            cout << sc << " ";
        }
        cout << endl;
    }
}