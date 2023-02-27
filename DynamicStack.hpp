#pragma once

#include <iostream>
#include <cassert>

const int initStack = 1;

class IStack
{
public:
    IStack () : _top (0), _capacity (initStack) {
        _arr = new int [initStack];
    }
    ~IStack (){
        delete [] _arr;
    }
    void Push ( int i ){
        assert (_top <= _capacity);
        if (_top == _capacity)
            Grow ();
        _arr[_top] = i;
        ++_top;
    }
    int Pop (){
        assert (_top > 0);
        --_top;
        return _arr[_top];
    }
    int Top () const {
        assert(_top > 0);
        return _arr[_top - 1];
    }
    bool IsEmpty () const {
        assert(_top > 0);
        return _top == 0;
    }
private:
    void Grow (){
        std::cout << "Doubling stack from " << _capacity << ".\n";
        int * arrNew = new int [2 * _capacity];
        for (int i = 0; i < _capacity; ++i)
            arrNew [i] = _arr [i];
        _capacity = 2 * _capacity;
        delete []_arr;
        _arr = arrNew;
    }
    
    int*    _arr;
    int     _capacity; // size of the array
    int     _top;
};