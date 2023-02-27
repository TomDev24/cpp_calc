#pragma once

#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <cassert>
#include <ctype.h>

enum EToken{
    tEnd,
    tError,
    tNumber, //Num
    tPlus,
    tMinus,
    tMult,
    tDivide,
    tLParen,
    tRParen,
    tAssgin, // =
    tIdent   // symbolic name

};

const int maxSymLen = 50;

class Scanner
{
public:
    Scanner(char const * buff);
    ~Scanner();

    EToken Accept();
    EToken Token() const { return _token;};
    double Number();
    void SymbolName(char* strOut, int& len);
private:
    void eatWhite();

    char const * const  _buff;
    int                 _iLook;
    int                 _iSymbol;
    int                 _lenSymbol;
    EToken              _token;
    double              _number;
};

void tokenDebug(EToken tkn);
