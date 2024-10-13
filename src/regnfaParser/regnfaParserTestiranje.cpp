#include "regnfaParser.cpp"

using namespace std;

int main(){

    RegnfaParser automat;

    string unos;
    cin>>unos;

    automat.parse(unos, "evo ga");


    automat.print();
    automat.finalPrint();


    return 0;
}
