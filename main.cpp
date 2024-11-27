#include <iostream>
#include "include/stack.h"

int main()
{
    Stack *newStack = new Stack();
    newStack->push(1, 2);
    newStack->push(3, 4);
    newStack->push(5, 6);
    newStack->push(7, 8);
    newStack->push(9, 10);
    newStack->push(8, 7);
    newStack->push(6, 5);
    newStack->push(4, 3);
    std::cout << newStack->stackSize() << std::endl;
    while (!newStack->isEmpty())
    {
        std::pair<int, int> output;
        output = newStack->getTop();
        std::cout << "{" << output.first << ";" << output.second << "}" << std::endl;
        newStack->pop();
    }
    std::cout << newStack->stackSize() << std::endl;
    newStack->push(1, 2);
    newStack->push(3, 4);
    newStack->push(5, 6);
    newStack->push(7, 8);
    newStack->push(9, 10);
    newStack->push(8, 7);
    newStack->push(6, 5);
    newStack->push(4, 3);
    std::cout << newStack->stackSize() << std::endl;
    newStack->clear();
    std::cout << newStack->stackSize() << std::endl;
}