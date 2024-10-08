#include "regnfaParser.h"

void RegnfaParser::printArray(int *polje[], int n){
    for(int i=0; i<n; i++){
        for (int j = 0; j < nes; j++){
            std::cout << polje[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void RegnfaParser::parse(std::string regex){

}