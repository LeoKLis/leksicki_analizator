#include "nfaDeserializer.h"

string NfaDeserializer::readChar(string& line)
{
    int firstBlank;
    if ((firstBlank = line.find_first_of(" ")) == string::npos) {
        return "npos";
    }
    string output = line.substr(0, firstBlank);
    line = line.substr(firstBlank + 1);
    return output;
}

vector<NFA> NfaDeserializer::deserializeNfas(string filePath)
{
    vector<NFA> nfaArr;
    ifstream nfaFile(filePath);
    string line;
    getline(nfaFile, line);

    // Cycles for every state in file
    while (getline(nfaFile, line)) {
        // Gets state name
        string stateName = line;

        // Gets all states and transitions
        NFA_STRUCTURE stateTransitions;
        while (getline(nfaFile, line) && line.length() != 0) {
            map<string, vector<int>> transition;
            readChar(line); // Skip first (its in order)
            string transitionChar = readChar(line); // Read transition character
            string transitionElement; // Read every state index that current state points to
            while ((transitionElement = readChar(line)) != "npos") {
                transition[transitionChar].push_back(stoi(transitionElement));
            }
            stateTransitions.push_back(transition);
        }
        // Gets all accept states and their actions
        map<int, vector<string>> acceptStatesMap;
        while (getline(nfaFile, line) && line.length() != 0) {
            int transitionIndex = stoi(readChar(line));
            vector<string> rules;
            string rule;
            while ((rule = readChar(line)) != "npos") {
                rules.push_back(rule);
            }
            acceptStatesMap[transitionIndex] = rules;
        }

        // Push everything to nfaArr
        nfaArr.push_back(NFA { stateName, stateTransitions, acceptStatesMap });
    }
    nfaFile.close();
    return nfaArr;
}

vector<string> NfaDeserializer::deserializeLexUnits(string filePath)
{
    vector<string> lexUnits;
    ifstream nfaFile(filePath);
    string line;
    getline(nfaFile, line);
    int emptyIndex;
    while ((emptyIndex = line.find_first_of(" ")) != string::npos) {
        lexUnits.push_back(line.substr(0, emptyIndex));
        line = line.substr(emptyIndex + 1);
    }
    nfaFile.close();
    return lexUnits;
}

void NfaDeserializer::printAcceptStates(vector<NFA> nfas)
{
    for (auto it : nfas) {
        cout << it.name << endl;
        for (auto se = it.acceptStatesMap.cbegin(); se != it.acceptStatesMap.cend(); se++) {
            cout << se->first << " ";
            for (auto th : se->second) {
                cout << th << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}

void NfaDeserializer::printNfas(vector<NFA> nfas)
{
    for (auto it : nfas) {
        cout << it.name << endl;
        int stateCount = 0;
        for (auto se : it.nfaStructure) {
            cout << stateCount++ << " ";
            for (auto th = se.cbegin(); th != se.cend(); th++) {
                cout << th->first << " ";
                for (auto fr : th->second) {
                    cout << fr << " ";
                }
            }
            cout << endl;
        }
        cout << endl;
    }
}