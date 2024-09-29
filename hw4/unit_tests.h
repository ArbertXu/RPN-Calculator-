#include "DatumStack.h"
#include "parser.h"
#include <cassert>
// tests to see if "stack" or list is created 
void testMakeStack()
{
    DatumStack Datums;
    assert(Datums.isEmpty());
}

// tests constructor which takes in array of datums and pushes it onto stack
void testSecondConstructor()
{
    Datum int_datum1(1);
    Datum int_datum2(2);
    Datum int_datum3(3);
    Datum int_datum4(4);
    Datum int_datum5(5);
    Datum test_arr[4] = {int_datum1, int_datum2, int_datum3, int_datum4};
    DatumStack thaStack(test_arr, 4);
    thaStack.push(int_datum5);
    assert(thaStack.size() == 5);
}

// tests clear function on a stack that has elements
void testClear()
{
    Datum int_datum1(1);
    Datum int_datum2(2);
    Datum int_datum3(3);
    Datum int_datum4(4);
    Datum int_datum5(5);
    Datum test_arr[4] = {int_datum1, int_datum2, int_datum3, int_datum4};
    DatumStack thaStack(test_arr, 4);
    thaStack.push(int_datum5);
    thaStack.clear();
    assert(thaStack.isEmpty());
}

// tests if top function returns the datum at the top of the stack
void testTop()
{
    Datum int_datum1(1);
    Datum int_datum2(2);
    Datum int_datum3(3);
    Datum int_datum4(4);
    Datum int_datum5(5);
    Datum test_arr[4] = {int_datum1, int_datum2, int_datum3, int_datum4};
    DatumStack thaStack(test_arr, 4);
    thaStack.push(int_datum5);
    assert(thaStack.top().getInt() == 5);
}

// tests popping elements off of the stack
void testPop()
{
    Datum int_datum1(1);
    Datum int_datum2(2);
    Datum int_datum3(3);
    Datum int_datum4(4);
    Datum int_datum5(5);
    Datum test_arr[4] = {int_datum1, int_datum2, int_datum3, int_datum4};
    DatumStack thaStack(test_arr, 4);
    thaStack.push(int_datum5);
    thaStack.pop();
    thaStack.pop();
    assert(thaStack.top().getInt() == 3);
}

// tests pushing a single element into the stack
void testPush()
{
    DatumStack thaStack;
    Datum data(true);
    thaStack.push(data);
    assert(thaStack.top().getBool());
}

// tests if correct error message is given when trying to get the top element
// of an empty stack
void test_empty_top(){
    DatumStack thaStack;
    bool runtime_error_thrown = false;
    std::string error_message = "";
    try {
        thaStack.top();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
    assert(runtime_error_thrown);
    assert(error_message == "empty_stack");
}

// test if correct error message is gven when trying to pop an element in an 
// empty stack
void test_empty_pop(){
    DatumStack thaStack;
    bool runtime_error_thrown = false;
    std::string error_message = "";
    try {
        thaStack.pop();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
    assert(runtime_error_thrown);
    assert(error_message == "empty_stack");
}