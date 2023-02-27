#pragma once

#include <iostream>
#include <limits.h>
#include <cstring>
#include <cassert>
#include "LinkeList.hpp"

/* inline bool IsDigitSlow (char c){
    return c >= '0' && c <= '9';
}*/

/*Hash Table. The hash table data structure is based on the idea of using table lookup 
to speed up an arbitary mapping*/

class CharTable{
public:
    CharTable (){
        for (int i = 0; i <= UCHAR_MAX; ++i){
            if (i >= '0' && i <= '9')
                _tab [i] = true;
            else
                _tab [i] = false;
        }
    }
    bool IsDigit (unsigned char c) { return _tab[c]; }
private:
    bool _tab[UCHAR_MAX + 1]; // limits.h
};

//CharTable TheCharTable;

const int sizeHTable = 127;

class HTable{
public:
    explicit HTable(int size = 127) : _size(size) {
        _aList = new List[size];
    }
    ~HTable(){
        delete [] _aList;
    }
    const List& Find(const char* str) const
    {
        return Find(str, strlen(str));
    }
    const List& Find(const char *str, int len) const {
        int i = hash(str);
        return _aList[i];
    };
    void Add(char const *str, int id){
        int i = hash(str);
        _aList[i].Add(id);
    }
private:
    //Read about diffrent hash fuctions
    int hash(char const *str) const {
        assert(str != 0 && str[0] != 0);
        unsigned h = str[0];
        for (int i = 1; str[i] != 0; ++i){
            h = (h << 4) + str[i];
        }
        return h % sizeHTable;
    };
    int     _size;
    List*   _aList;
    //List _aList[sizeHTable];
};
