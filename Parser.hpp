#pragma once

#include <iostream>
#include "Node.hpp"
#include "Store.hpp"
#include "Scanner.hpp"
#include "StringTable.hpp"
//#include "SymbolTable.hpp"

/*
class Node;
class Scanner;
class Store;
class FunctionTable;
class SymbolTable;
*/

enum Status{
    stQuit,
    stError,
    stOk
};

class Parser
{
public:
    Parser(Scanner& scanner,
        Store& store, 
        StringTable& symbolTable);
    ~Parser();
    Status Eval();
private:
    Status  Parse();
    void    Execute();

    Node*   Expr();
    Node*   Term();
    Node*   Factor();

    Status          _status;
    Scanner&        _scanner;
    Store&          _store;
    Node*           _pTree;
    StringTable&    _symbolTable;
};

