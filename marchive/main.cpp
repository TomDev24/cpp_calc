#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <iostream>

//in c++ 11 can use std::stoi(str)

int check_precedence(char a){
    std::string lev1 = "*/";
    std::string lev0 = "+-";

    //c++ way
    //if (s1.find(s2) != std::string::npos) { std::cout << "found!" << '\n';}
    //printf("Text* %s\n", &a);        
    /*
    if (strstr(lev1.c_str(), &a) != NULL){
        printf("Char* %c\n", a);        
        return 0;
    }
    else
        return 1;
    */
    if (strchr(lev1.c_str(), a) != NULL)
        return 0;
    else
        return 1;

} 

char compare_precedence(char a, char b){
    if (check_precedence(a) >= check_precedence(b)){
        std::cout << "__" << std::endl;
        std::cout << a << std::endl;
        std::cout << b << std::endl;
        std::cout << "__" << std::endl;
        return 1;
    }
    else
        return 0;
}

template <class T>
void print_stack(T *stack, int sp){
    int i = 0;
    while (i < sp){
        std::cout << stack[i];
        i++;
    }

    std::cout << std::endl;
}

char is_operation(std::string &input){
    if (input == "+")
        return 1;
    else if (input == "-")
        return 1;
    else if (input == "*")
        return 1;
    else if (input == "/")
        return 1;
    return 0;
}

int get_from_stack(char *stack, int op_sp);
int put_to_stack();

void solve(int *output, int out_sp, char *op_stack, int op_sp){
    int stack[1000];
    int sp = 0;
    int i = 0;

    print_stack(output, out_sp);
    print_stack(op_stack, op_sp);
    //we need to add 
    for (int i = 0; i < op_sp; i++){
        output[out_sp++] = op_stack[i];
    }
    while (i < out_sp){
        int c = output[i];
        std::cout <<  "char: " << (char)c << "int: "<< c << std::endl;
        switch (c) {
             case '+':
                stack[sp-2] = stack[sp-2] + stack[sp-1];  sp--;
                break;
             case '-':
                stack[sp-2] = stack[sp-2] - stack[sp-1];  sp--;
                break;
             case '*':
                stack[sp-2] = stack[sp-1] * stack[sp-2];  sp--;
                break;
             case '/':
               stack[sp-2] = stack[sp-2] / stack[sp-1];   sp--;
                break;
             default:
                stack[sp] = output[i];                       sp++;
        }
        i++;
    }
    printf("Result = %d\n", stack[sp - 1]);  sp--;
}

int main(int argc, char const *argv[])
{
    int output[1000];
    char op_stack[1000];
    memset(output, 0, sizeof(int) * 1000);
    memset(op_stack, 0, sizeof(char) * 1000);

    int out_sp = 0; // top is out_sp - 1
    int op_sp = 0; // top is _________

    std::string input; 
    std::cin >> input;
    //We need pop OPERATOR FROM THE END!!!!!!!!!!!!!!
    while (input != "exit"){
        if (is_operation(input)){
            while (op_stack[op_sp-1] != 0 && compare_precedence(*input.c_str(), op_stack[op_sp-1])){
                if (op_sp == 0)
                   break;
                output[out_sp++] = op_stack[--op_sp];
            }
            op_stack[op_sp++] = *input.c_str();
        }
        else{
            output[out_sp++] = atoi(input.c_str());
        }
        std::cin >> input;
    }

    solve(output, out_sp, op_stack, op_sp);
    return 0;
}
