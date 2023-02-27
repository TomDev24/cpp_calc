#pragma once

class Link
{
public:
    Link (Link* pNext, int id) : _pNext (pNext), _id (id) {}
    Link* Next() const { return _pNext; }
    int Id() const { return _id; }
private:
    int     _id;
    Link*   _pNext;
};

class List
{
public:
    List() : _pHead(0) {}
    ~List(){
        //destruction of list could be done recursivly
        while ( _pHead != 0 ){
            Link* pLink = _pHead;
            _pHead = _pHead->Next();
            delete pLink;
        }
    }
    void Add( int id ){
        // add in front of the list
        Link * pLink = new Link (_pHead, id);
        _pHead = pLink;
    }
    Link const * GetHead () const { return _pHead; }
private:
    Link*   _pHead;
};


/*
for (Link const * pLink = list.GetHead();
    pLink != 0;
    pLink = pLink->Next ())
{
    if (pLink->Id() == id)
        break;
}
*/