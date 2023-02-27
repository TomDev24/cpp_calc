#pragma once

#include <cstring>
#include <iostream>

const int maxBufSize = 500;

//Storing null terminated string in one char* array
class StringBuffer
{
public:
    StringBuffer() : _curOffset(0) {};
    int GetOffset() const {
        return _curOffset;
    }
    //
    bool WillFit(int len) const {
        return _curOffset + len + 1 < maxBufSize;
    }
    //
    void Add(const char *str){
        strcpy(&_buf[_curOffset], str);
        _curOffset += strlen(str) + 1;
    }
    bool isEqual(int offset, const char* str) const{
        char const * strStored = &_buf[offset];
        return strcmp(str, strStored) == 0;
    }
    const char* GetString(int offset) const {
        return &_buf[offset];
    }
private:
    char    _buf[maxBufSize];
    int     _curOffset; // index for next string insertion
};
