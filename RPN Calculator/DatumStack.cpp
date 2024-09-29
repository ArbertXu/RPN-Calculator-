/*
 *  Datum
 *  Arbert Xu (axu10)
 *  2/27/24
 *
 *  COMP 15 HW 4 CalcYouLater
 *
 *  This file initializes all of the functions for the DatumStack class. 
 *  It esentially is all the functions that a stack has plus an extra 
 *  constructor which can read in an array of Datums and add them to the 
 *  stack. These functions are used by RPNCalc function.
 *
 */
#include "DatumStack.h"
#include <stdexcept>
using namespace std;

/* DatumStack::DatumStack()
Purpose: Initializes the DatumStack, initializes the list.
Parameters: N/A
Return: N/A
*/ 
DatumStack::DatumStack()
{

}
/* DatumStack::DatumStack(Datum info[], int size)
Purpose: Initializes the DatumStack with the elements inside the array of 
Datum.
Parameters: Datum info[], int size. Int size to know how many elements 
to be added and an array of Datum to be pushed into the stack.
Return: N/A
*/ 
DatumStack::DatumStack(Datum info[], int size)
{
    for(int i = 0; i < size; i++)
    {
        push(info[i]);
    }
}
/* bool DatumStack::isEmpty()
Purpose: Checks to see if the DatumStack is empty. True if yes, false if not.
Parameters: N/A
Return: Bool true or false depending on if the DatumStack is empty.
*/ 
bool DatumStack::isEmpty()
{
    return stack.empty();
}
/* void DatumStack::clear()
Purpose: clears all elements of the DatumStack.
Parameters: n/A
Return: N/A
*/ 
void DatumStack::clear()
{
    stack.clear();
}
/* int DatumStack::size()
Purpose: gets the size of the DatumStack and returns it.
Parameters: N/A
Return: an int of the size of the DatumStack
*/ 
int DatumStack::size()
{
    return stack.size();
}

/* Datum DatumStack::top()
Purpose: Gets the top Datum of the stack and returns it. If the DatumSTack is 
empty, will throw an error.
Parameters: N/A
Return: The Datum at the top of the DatumSTack.
*/ 
Datum DatumStack::top()
{
    if(isEmpty())
    {
        throw std::runtime_error("empty_stack");
    }
    return stack.front();
}
/* void DatumStack::pop()
Purpose: Removes the top element of the DatumStack. Will throw an error if 
the DatumStack is empty.
Parameters: N/A
Return: N/A
*/ 
void DatumStack::pop()
{
    if(isEmpty())
    {
        throw std::runtime_error("empty_stack");
    }
    stack.pop_front();
}
/* void DatumStack::push(Datum stuff)
Purpose: Pushes an element to the top of the DatumStack. 
Parameters: Datum stuff which is pushed onto the top of the DatumStack.
Return: N/A
*/ 
void DatumStack::push(Datum stuff)
{
    stack.push_front(stuff);
}