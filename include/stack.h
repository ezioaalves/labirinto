#include <iostream>
#include <utility>
#include "cell.h"

class Stack
{
private:
    int size;
    Cell *top;

public:
    Stack();
    void push(int x, int y);            // Adds an element to the top.
    void pop();                         // Removes the top element.
    std::pair<int, int> getTop() const; // Returns a reference to the top element.
    bool isEmpty() const;               // Checks if the stack is empty.
    int stackSize() const;              // Returns the number of elements.
    void clear();                       // Removes all elements from the stack.
};