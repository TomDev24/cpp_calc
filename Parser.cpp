#include "Parser.hpp"

Parser::Parser(Scanner& scanner, Store& store, StringTable& symbolTable) :
    _scanner(scanner),
    _store(store),
    _symbolTable(symbolTable),
    _pTree(0),
    _status(stOk)
{}

Parser::~Parser()
{
    delete _pTree;
}

void Parser::Execute(){
    if (_pTree){
        std::cout << "  " << _pTree->Calc() << std::endl;
    }
}

Status Parser::Eval(){
    //return stQuit;
    Parse();
    if (_status == stOk)
        Execute();
    else
        _status = stQuit;
    return _status;
}


Node* Parser::Factor(){
    Node* pNode;
    EToken token = _scanner.Token();

    //tokenDebug(token);
    if (token == tNumber){
        std::cout << "Num is " << _scanner.Number() << std::endl;
        pNode = new NumNode(_scanner.Number());
        _scanner.Accept();
    } else if (token == tLParen){
        _scanner.Accept();
        pNode = Expr();
        if (_scanner.Token() != tRParen)
            _status = stError;
        _scanner.Accept();
    } else if (token == tIdent){
        char strRes[maxSymLen + 1];
        int strLen = maxSymLen;

        _scanner.SymbolName(strRes, strLen);
        int id = _symbolTable.Find(strRes);
        _scanner.Accept();

        if (id == idNotiFound)
            id = _symbolTable.ForceAdd(strRes);
        pNode = new VarNode(id, _store);
    } else {
        _scanner.Accept();
        std::cout << "setting error here" << std::endl;
        _status = stError;
        pNode = 0;
    }

    return pNode;
}

Node* Parser::Term(){
    Node* pNode = Factor();
    EToken token = _scanner.Token();

    //tokenDebug(token);
    if (token == tMult){
        _scanner.Accept();
        Node *pRight = Term();
        pNode = new MultNode(pNode, pRight);
    } else if (token == tDivide){
        _scanner.Accept();
        Node *pRight = Term();
        pNode = new DivNode(pNode, pRight);
    }
    return pNode;
}

Node* Parser::Expr(){
    Node* pNode = Term();
    EToken token = _scanner.Token();

    //tokenDebug(token);
    if (token == tPlus){
        _scanner.Accept();
        Node *pRight = Expr();
        pNode = new AddNode(pNode, pRight);
    } else if (token == tMinus){
        _scanner.Accept();
        Node *pRight = Expr();
        pNode = new SubNode(pNode, pRight);
    } else if (token == tAssgin){
        _scanner.Accept();
        if (!pNode->IsLvalue()){
            std::cout << "Settign error in lvalue\n";
            _status = stError;
        } else{
            Node *pRight = Expr();
            pNode = new AssignNode(pNode, pRight);
        }
    }
    return pNode;
}

void printStatus(Status st){
    if (st == stQuit)
        std::cout << "stQuit\n";
    if (st == stError)
        std::cout << "stError\n";
    if (st == stOk)
        std::cout << "stOk\n";
}

Status Parser::Parse(){
    _pTree = Expr();

    std::cout << "######\n";
    printStatus(_status);
    std::cout << _pTree << ":Tree " << std::endl;
    std::cout << _pTree->Calc() << std::endl;
    std::cout << "######\n";
    return _status;
}