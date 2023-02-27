#pragma once

#include <iostream>
#include <cassert>
#include "Store.hpp"

class Node{
public:
    virtual         ~Node(){}
    virtual double  Calc() const = 0;
    virtual void    assign(double val) {}
    virtual bool    IsLvalue () const
    {
        return 0;
    }
};

class NumNode : public Node{
public:
    NumNode(double num) : _num(num){}
    virtual double Calc() const { return _num; }
private:
    const double _num;
};

class BinNode : public Node {
public:
    BinNode(Node *pLeft, Node *pRight) : _pLeft(pLeft), _pRight(pRight) {}
    ~BinNode(){
        delete _pLeft;
        delete _pRight;
    }
protected:
    Node * const    _pLeft;
    Node * const    _pRight;
};

class AddNode : public BinNode{
public:
    AddNode(Node *pLeft, Node *pRight) : BinNode(pLeft, pRight) {}
    virtual double Calc() const { return _pLeft->Calc() + _pRight->Calc(); }
};

class SubNode : public BinNode{
public:
    SubNode(Node *pLeft, Node *pRight) : BinNode(pLeft, pRight) {}
    virtual double Calc() const { return _pLeft->Calc() - _pRight->Calc(); }
};

class MultNode : public BinNode{
public:
    MultNode(Node *pLeft, Node *pRight) : BinNode(pLeft, pRight) {}
    virtual double Calc() const { return _pLeft->Calc() * _pRight->Calc(); }
};

class DivNode : public BinNode{
public:
    DivNode(Node *pLeft, Node *pRight) : BinNode(pLeft, pRight) {}
    virtual double Calc() const { return _pLeft->Calc() / _pRight->Calc(); }
};

class AssignNode : public BinNode{
public:
    AssignNode(Node *pLeft, Node *pRight) : BinNode(pLeft, pRight) {
        assert(_pLeft->IsLvalue()); // parser should not give us inccorect node
    }
    virtual double Calc() const {
        double res = _pRight->Calc();
        _pLeft->assign(res);
        return res;
    }
};

// Class Store; // Again in header he uses forward declaration
// and includes only in cpp file

class VarNode : public Node {
public:
    VarNode(int id, Store& store) : _id(id), _store(store) {}
    virtual bool    IsLvalue () const {
        return true;
    }
    virtual void assign (double val)
    {
        _store.SetValue (_id, val);
    }
    virtual double Calc () const {
        double res = 0.0;
        if (_store.IsInit(_id))
            res = _store.Value(_id);
        else
            std::cout << "Uninit variable!!\n";
        return res;
    }
private:
    const int   _id;
    Store&      _store;
};