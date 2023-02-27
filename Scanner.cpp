#include "Scanner.hpp"

void tokenDebug(EToken tkn){
    switch (tkn)
    {
    case tEnd:
        std::cout << "tEnd" << std::endl;
        break;
    case tError:
        std::cout << "tError" << std::endl;
        break;
    case tNumber:
        std::cout << "tNumber" << std::endl;
        break;
    case tPlus:
        std::cout << "tPlus" << std::endl;
        break;
    case tMinus:
        std::cout << "tMinus" << std::endl;
        break;
    case tMult:
        std::cout << "tMult" << std::endl;
        break;
    case tDivide:
        std::cout << "tDivide" << std::endl;
        break;
    case tAssgin:
        std::cout << "tAssgin" << std::endl;
        break;
    case tIdent:
        std::cout << "tIdent" << std::endl;
        break;
    case tLParen:
        std::cout << "tLParen" << std::endl;
        break;
    case tRParen:
        std::cout << "tRParen" << std::endl;
        break;
    default:
        std::cout << "Unkdown token\n";
        break;
    }
    //tLParen,
    //tRParen,
}



Scanner::Scanner(char const * buff): 
    _buff(buff),
    _iLook(0)
{
    this->Accept();
}

Scanner::~Scanner()
{
}

EToken Scanner::Accept(){
    eatWhite();
    switch (_buff[_iLook])
    {
    case '+':
        _token = tPlus;
        _iLook++;
        break;
    case '-':
        _token = tMinus;
        _iLook++;
        break;
    case '*':
        _token = tMult;
        _iLook++;
        break;
    case '/':
        _token = tDivide;
        _iLook++;
        break;
    case '(':
        _token = tLParen;
        _iLook++;
        break;
    case ')':
        _token = tRParen;
        _iLook++;
        break;
    case '=':
        _token = tAssgin;
        _iLook++;
        break;
    case '\0':
        _token = tEnd;
        break;
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    case '.':
        _token = tNumber;
        char *p;
        _number = std::strtod(&_buff[_iLook], &p);
        //_iLook += p - _buff; //my idea
        _iLook = p - _buff;
        //_number = atoi(&_buff[_iLook]);
        //while( isdigit(_buff[_iLook]) )
        //    ++_iLook;
        break;
    default:
        if(isalpha(_buff[_iLook]) || _buff[_iLook] == '_'){
            _token = tIdent;
            _iSymbol = _iLook;
            int cLook; // inited in do loop
            do{
                ++_iLook;
                cLook = _buff[_iLook];
            } while (isalnum(cLook) || cLook == '_');

            _lenSymbol = _iLook - _iSymbol;
            if (_lenSymbol > maxSymLen){
                _lenSymbol =maxSymLen;
            }
        } else
            _token = tError;
        break;
    }
    std::cout << "Indide scanner: ";
    tokenDebug(_token);
    return _token;
}

void Scanner::SymbolName(char* strOut, int& len){
    assert (len >= maxSymLen);
    assert (_lenSymbol <= maxSymLen);
    strncpy(strOut, &_buff[_iSymbol], _lenSymbol);
    strOut[_lenSymbol] = 0;
    len = _lenSymbol;
}

double Scanner::Number(){
    assert(_token == tNumber);
    return _number;
}

void Scanner::eatWhite(){
    while (isspace(_buff[_iLook]))
        ++_iLook;
}