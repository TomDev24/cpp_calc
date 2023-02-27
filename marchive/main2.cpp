#include <iostream>
#include <stdlib.h>
#include <string.h>

const char *operators = "*/+-";

int get_precedence(char a){
    if (a == '*' || a == '/')
        return 1;
    else
        return 0;
}

int compare_precedence(int a, int b){
    if (get_precedence(a) >= get_precedence(b))
        return 1;
    else
        return 0;
}

//fix hardcoded size
template <class T>
class Stack{
private:
    T   stack[1000];
    int sp;
public:
    Stack(){
        sp = 0; // points on empty value which gonna be set
        memset(stack, 0, sizeof(T) * 1000);
    }
    void push(T value){
        if (sp == 1000)
            throw std::runtime_error("Stack limit is reached");
        stack[sp++] = value;
    }
    void push_offset(T value, int i){
        //i is offset
        int temp1;
        int temp2;

        int j = 1;
        while (sp - i + j < sp){
            temp1 = stack[sp - i + j];
            if (j == 1){
                stack[sp - i + j] = value;
                sp++;
            }
            else
                stack[sp - i + j] = temp2;
            temp2 = temp1;
            j++;
        }
    }
    //returns number of compare
    int compare_push(T value, int (*compare)(int, int)){
        int i = 1;
        int temp1;
        int temp2;

        if (sp == 0){
            push(value);
            return 0;
        }
        //while top of stack has >= precedence than new value
        while (sp - i >= 0 && compare(stack[sp - i ], value)){
            std::cout << "Check comp: " << compare(stack[sp - i ], value) << std::endl;
            i++;
        }
        std::cout << "i: " << i << std::endl;
        int j = 1;
        while (sp - i + j < sp + 1){
            temp1 = stack[sp - i + j];
            if (j == 1){
                stack[sp - i + j] = value;
                sp++;
            }
            else
                stack[sp - i + j] = temp2;
            std::cout << "SP " << sp << std::endl;
            std::cout << "Putted " << stack[sp - i + j]  << " " << sp -i + j << std::endl;
            temp2 = temp1;
            j++;
        }
        //shift all values on one cell to the right
        return i;
    }
    T pop(){
        if (sp == 0)
            throw std::runtime_error("Nothing to pop from stack");
        return stack[--sp];
    }
    void merge(Stack<T> &other){

    }

    void print(){
        //sp - 1 is the top of the stack
        for (int i = sp ; i >= 0; i--){
            std::cout << stack[i] << std::endl;
        }
    }
    ~Stack(){};
};

void test(){
    Stack<int> s;
    s.push(123);
    s.push(8);
    s.push(5);
    s.print();
    int val = s.pop();   
    std::cout << "Poped the value " << val << std::endl;
    s.print();
}

int simp(int a, int b){
    if (a > b)
        return 1;
    else
        return 0;
}

void test2(){
    Stack<int> s;

    s.compare_push(6, simp);
    s.compare_push(8, simp);
    s.compare_push(2, simp);

    s.print();
}


//parser may require some addition
Stack<int> *parse(std::string &input){
    Stack<int> *out_stack = new Stack<int>;
    Stack<int> op_stack;
    int steps = 0;    

    int i = 0;
    while (i < input.size()){
        //if its opertaion
        if (strchr(operators, input[i])){
            //op_stack.push(input[i]);

            //when we encounter lower precedence
            //we need to put number lower
            steps = op_stack.compare_push(input[i], compare_precedence);
        }
        //if its number
        else if ( isdigit(*(input.c_str() + i)) ){
            if (steps)
                out_stack->push_offset( atoi(input.c_str() + i), steps );
            else
                out_stack->push( atoi(input.c_str() + i) );
            while ( isdigit(*(input.c_str() + i)) )
                i++;
            continue; 
        }
        i++;
    }

    std::cout << "Num stack" << std::endl; out_stack->print();
    std::cout << "Opertaion stack" << std::endl; op_stack.print();
    return out_stack;
}

void solve(Stack<int> &output){

}

int main(int argc, char const *argv[])
{
    //test2();
    //return 0;
    Stack<int> *output;
    std::string input; 
    std::cin >> input; 
    while (input != "ex"){
        output = parse(input);
        solve(*output);
        std::cin >> input; 
    }
    return 0;
}
