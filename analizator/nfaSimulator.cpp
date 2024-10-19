#include "nfaSimulator.h"

NfaSimulator::NfaSimulator(vector<NFA> nfaovi)
{
    automati = nfaovi;
    currentState = 0;
    redak = 1;
    pocetak = 0;
    zavrsetak = 0; // Iterator index
    posljednji = -1;

    for (int i = 0; (size_t)i < nfaovi.size(); i++)
        nfaNames.insert({ nfaovi[i].name, i });
}

void NfaSimulator::doAction(vector<string> actions, string niz)
{
    Row row;
    bool toFinalTable = false;
    bool ignoreString = false;
    for (auto act : actions) {
        if (act == "NOVI_REDAK")
            redak = redak + 1;
        else if (act == "-"){
            ignoreString = true;
            continue;
        }
        else if (act.substr(0, act.find(" ")) == "VRATI_SE") {
            int broj = stoi(act.substr(act.find(" ") + 1));
            posljednji = pocetak + broj;
        } else if (act.substr(0, act.find(" ")) == "UDJI_U_STANJE") {
            string newState = act.substr(act.find(" ") + 1);
            currentState = nfaNames.at(newState);
            automati[currentState].restart();
        } else {
            row.lexUnit = act;
            row.rowNumber = redak;
            toFinalTable = true;
        }
    }
    if (toFinalTable && !ignoreString) {
        row.uniformSymbol = niz.substr(0, posljednji - pocetak);
        finalTable.push_back(row);
    }
}

void NfaSimulator::loadFromStdin()
{
    string input;
    getline(cin, input);
    codeString.append(input);
    while (getline(cin, input)) {
        codeString.append("\n" + input);
    }
    codeString.append("  ");
}

void NfaSimulator::simulate()
{
    vector<string> izraz;

    while ((size_t)zavrsetak < codeString.length()) {
        char znak = codeString[zavrsetak];
        switch (automati[currentState].isFinished()) {
        case 0:
            automati[currentState].readChar(znak);
            zavrsetak = zavrsetak + 1;
            break;
        case 1:
            izraz = automati[currentState].getAction();
            posljednji = zavrsetak;
            zavrsetak += 1;
            automati[currentState].readChar(znak);
            break;
        case 2:
            if (izraz.empty()) {
                automati[currentState].restart();
                pocetak = pocetak + 1;
                zavrsetak = pocetak;
            } else {
                string niz = codeString.substr(pocetak, posljednji - pocetak);
                doAction(izraz, niz);
                izraz.clear();
                posljednji -= 1;
                pocetak = posljednji + 1;
                zavrsetak = pocetak;
                automati[currentState].restart();
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

void NfaSimulator::printAsSource()
{
    int currentRow = 1;
    cout << "1\t";
    for (auto it : finalTable) {
        if (currentRow != it.rowNumber) {
            currentRow = it.rowNumber;
            cout << endl
                 << it.rowNumber << "\t";
        }
        cout << it.uniformSymbol << " ";
    }
    cout << endl;
}