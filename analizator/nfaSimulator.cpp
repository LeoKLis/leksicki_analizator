#include "nfaSimulator.h"

NfaSimulator::NfaSimulator(vector<NFA> nfaovi)
{
    automati = nfaovi;
    currentState = 0;
    redak = 1;
    pocetak = 0;
    zavrsetak = 0; // Iterator index
    posljednji = -1;

    for (int i = 0; i < nfaovi.size(); i++)
        nfaNames.insert({ nfaovi[i].name, i });
}

void NfaSimulator::doAction(vector<string> actions, string niz)
{
    for (auto act : actions) {
        if (act == "NOVI_REDAK")
            redak = redak + 1;
        else if (act == "-")
            continue;
        else if (act.substr(0, act.find(" ")) == "VRATI_SE") {
            int broj = stoi(act.substr(act.find(" ") + 1));
            posljednji = pocetak + broj - 1;
        } else if (act.substr(0, act.find(" ")) == "UDJI_U_STANJE") {
            string newState = act.substr(act.find(" ") + 1);
            currentState = nfaNames.at(newState);
            automati[currentState].restart();
        } else {
            Row row;
            row.lexUnit = act;
            row.rowNumber = redak;
            row.uniformSymbol = niz;
            finalTable.push_back(row);
        }
    }
}

void NfaSimulator::loadFromStdin(){
    ifstream file("c_program.c");
    string input;
    getline(file, input);
    codeString.append(input);
    while(getline(file, input)){
        codeString.append("\\n" + input);
    }
}
// 
void NfaSimulator::simulate()
{
    vector<string> izraz;
    
    while (zavrsetak < codeString.length()) {
        char znak = codeString[zavrsetak];
        switch (automati[currentState].isFinished()) {
        case 0:
            if(!automati[currentState].readChar(znak)){
                zavrsetak = zavrsetak + 1;
                znak = codeString[zavrsetak];
                automati[currentState].readChar(znak);
            }
            zavrsetak = zavrsetak + 1;
            break;
        case 1:
            izraz = automati[currentState].getAction();
            posljednji = zavrsetak;
            zavrsetak = zavrsetak + 1;
            if(!automati[currentState].readChar(znak)){
                posljednji += 1;
                zavrsetak += 1;
                znak = codeString[zavrsetak];
                automati[currentState].readChar(znak);
            }
            break;
        case 2:
            if (izraz.empty()) {
                automati[currentState].restart();
                pocetak = pocetak + 1;
                zavrsetak = pocetak;
            } else {
                string niz = codeString.substr(pocetak, posljednji - pocetak);
                doAction(izraz, niz); // TREBA DODATI NIZ SIMBOLA KOJI SE KORISTE
                izraz.clear();
                pocetak = posljednji + 1;
                zavrsetak = pocetak;
            }
            break;
        }
    }
}

void NfaSimulator::printTable()
{
    for (auto it : finalTable) {
        cout << it.lexUnit << " " << it.rowNumber << " " << it.uniformSymbol << "\n";
    }
}