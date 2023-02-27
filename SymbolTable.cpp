#include "SymbolTable.hpp"


SymbolTable::SymbolTable(int size) :
    _size(size),
    _curId(0),
    _curStrOff(0),
    _htab(size + 1)
{
    _offStr = new int [size];
    _bufSize = size * 10;
    _strBuf = new char [_bufSize];
}

SymbolTable::~SymbolTable()
{
    delete [] _offStr;
    delete [] _strBuf;
}
