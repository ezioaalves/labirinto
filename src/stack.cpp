#include <stdexcept>
#include "../include/stack.h"

Stack::Stack(){
    size = 0;
    top = nullptr;
}

void Stack::push(int x, int y) // Adds an element to the top.
{
    Plate* newPlate = new Plate(x,y);
    newPlate->next = top;
    top = newPlate;
    size++;
}

void Stack::pop() // Removes the top element.
{
    if(isEmpty()){
        throw std::out_of_range( "Empty List!" );
    }
    Plate* output = top;
    top = top->next;
    delete output;
    size--;
}

std::pair<int, int> Stack::getTop() const // Returns a reference to the top element.
{
    if(isEmpty()){
        throw std::out_of_range( "Empty List!" );
    }
    return std::make_pair(top->x, top->y);
}
bool Stack::isEmpty() const // Checks if the stack is empty.
{
    return top==nullptr;
}
int Stack::stackSize() const // Returns the number of elements.
{
    return size;
}
void Stack::clear() // Removes all elements from the stack.
{
    while(!isEmpty()){
        pop();
    }
}