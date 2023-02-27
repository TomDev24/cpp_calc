#pragma once

#include <iostream>
#include "HashTable.hpp"

const int idNotFound = -1;

class SymbolTable
{
public:
    explicit SymbolTable(int size);
    ~SymbolTable();
    int ForceAdd(const char *str, int len);
    int Find(const char *str, int len) const;
    char const * GetString(int id) const;
private:
    HTable  _htab;
    int*    _offStr; // offsets of strings in buffer
    int     _curId;
    int     _size;
    char*   _strBuf;
    int     _bufSize;
    int     _curStrOff;
};

