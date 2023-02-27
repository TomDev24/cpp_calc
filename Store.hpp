#pragma once

#include <cassert>
#include <math.h>
//#include "SymbolTable.hpp" // He says its not very efficient
#include "StringTable.hpp"

enum {stNotInit, stInit};
//class SymbolTable; // forward declaration

class Store
{
public:
    Store (int size, StringTable & symTab) : _size(size){
        _cell = new double [size];
        _status = new unsigned char [size];
        for (int i = 0; i < size; ++i)
            _status [i] = stNotInit;
        
        // add predefined constants
        // Note: if more needed, do a more general job
        std::cout << "e = " << exp(1) << std::endl;
        int id = symTab.ForceAdd ("e");
        SetValue (id, exp(1));
        std::cout << "pi = " << 2 * acos (0.0) << std::endl;
        id = symTab.ForceAdd ("pi");
        SetValue (id, 2.0 * acos (0.0));
    }
    ~Store (){
        delete []_cell;
        delete []_status;
    }
    bool IsInit (int id) const{
        return (id < _size && _status [id] != stNotInit);
    }
    double Value (int id) const {
        assert (IsInit (id));
        return _cell [id];
    }
    void SetValue (int id, double val)
    {
        if (id < _size){
            _cell [id] = val;
            _status [id] = stInit;
        }
    }
private:
    int             _size;
    double*         _cell;
    unsigned char*  _status;
};

/*
The constructor of Store is defined in the source file store.cpp.
Since the constructor calls actual methods of the SymbolTable, the
forward declaration of this class is no longer sufficient and we need to
explicitly include the header symtab.h in store.cpp.
*/