#ifndef REGNFA_PARSER_H
#define REGNFA_PARSER_H

#include<string>
#include<iostream>

class RegnfaParser {
private:
    void printArray(int *polje[], int n);
public:
    static void parse(std::string regex);
};


#endif /*REGNFA_PARSER_H*/