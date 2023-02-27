#include <iostream>
#include <cassert>

#include "Scanner.hpp"
#include "StringTable.hpp"
#include "Parser.hpp"
#include "Store.hpp"

const int buff_size = 100;


int main(int argc, char const *argv[])
{
    Status      status;
    StringTable symTable;
    Store       store(100, symTable);
    char        buff[buff_size];

    do{
        std::cout << "> ";
        std::cin.getline(buff, buff_size);
        Scanner scanner(buff);
        Parser parser(scanner, store, symTable);
        status = parser.Eval();
    }while (status != stQuit);
    
    std::cout << "Input: " << buff << std::endl;
    return 0;
}


/*
#include "DynamicStack.hpp"
int main ()
{
    IStack stack;
    for (int i = 0; i < 5; ++i){
        std::cout << "Push " << i << std::endl;
        stack.Push (i);
    }
    for (int j = 0; j < 5; ++j)
        std::cout << "Pop " << stack.Pop () << std::endl;
}
*/

/*
#include "LinkeList.hpp"
int main(int argc, char const *argv[])
{
    List list;

    list.Add(5); list.Add(30); list.Add(42);
    list.Add(99); list.Add(88);
    for (Link const * pLink = list.GetHead();
        pLink != 0;
        pLink = pLink->Next())
    {
        std::cout << pLink->Id() << std::endl;
        if (pLink->Id() == 42)
            std::cout << "Found 42\n";
            break;
    }
    return 0;
}
*/


/*
//String Table and Store class test
//Which has StringBuffer, HTable
//HTable has List(Linked List)
#include "StringTable.hpp"
#include "Store.hpp"
int main(){
    StringTable table;
    int         ids[30];
    int         i;

    ids[0] = table.ForceAdd("First string");
    ids[1] = table.ForceAdd("Another string(second)");
    ids[2] = table.ForceAdd("Hope it all works!");

    std::cout << table.GetString(ids[0]) << "\n";
    std::cout << table.GetString(ids[1]) << "\n";
    std::cout << table.GetString(ids[2]) << "\n";
    std::cout << "\n";

    i = table.Find("Hope it all works!"); 
    std::cout << "Find 'Hope it all works! :" << table.GetString(i) << "\n";
    std::cout << "##########\n";

    //store will add 'e' and 'p' to 3, 4 index of stringTable
    Store store(100, table);
    
    //std::cout << "Find 'e' value: " << table.Find("e") << std::endl;
    std::cout << "Find 'e' value: " << store.Value(table.Find("e")) << std::endl;
    return 0;
}
*/

/*
#include "Node.hpp"
int main ()
{
    // ( 20.0 + (-10.0) ) * 0.1
    Node * pNode1 = new NumNode (20.0);
    Node * pNode2 = new NumNode (-10.0);
    Node * pNode3 = new AddNode (pNode1, pNode2);
    Node * pNode4 = new NumNode (0.1);
    Node * pNode5 = new MultNode (pNode3, pNode4);
    std::cout << "Calculating the tree\n";
    // tell the root to calculate itself
    double x = pNode5->Calc ();
    std::cout << x << "\n";
    delete pNode5; // and all children
}
*/