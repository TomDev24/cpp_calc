#pragma once

#include <iostream>
#include <cstring>
#include "HashTable.hpp"
#include "StringBuffer.hpp"

const int idNotiFound = -1;
const int maxStrings = 100;

// String table maps strings to ints, and ints to strings
class StringTable
{
public:
    StringTable() : _curId(0) {}
    ~StringTable() {};
    //ignoring his len pass bullshit
    int ForceAdd(const char *str){
        int len = strlen(str);
        if (_curId == maxStrings || !_strBuf.WillFit(len))
            return idNotiFound;

        _offStr[_curId] = _strBuf.GetOffset(); 
        _strBuf.Add(str);

        _htab.Add(str, _curId);
        ++_curId;
        return _curId - 1;
    }
    int Find(const char *str) const {
        const List& list = _htab.Find(str);
        for (const Link* head = list.GetHead();
            head != 0;
            head = head->Next())
        {
            int id = head->Id();
            int offStr = _offStr[id];
            if (_strBuf.isEqual(offStr, str))
                return id;
        }
        return idNotiFound;
    }
    const char* GetString(int id) const {
        assert (id >= 0);
        assert (id < _curId);
        int offStr = _offStr [id];
        return _strBuf.GetString (offStr);
    }
private:
    HTable          _htab;
    int             _offStr[maxStrings];
    int             _curId;
    StringBuffer    _strBuf;
};
