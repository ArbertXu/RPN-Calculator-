/*
 *  Datum
 *  Arbert Xu (axu10)
 *  2/27/24
 *
 *  COMP 15 HW 4 CalcYouLater
 *
 *  This file creates the DatumStack class. A DatumStack is used in RPNCalc to
 *  store different Datums to compute. It allows for adding and popping 
 *  elements when computations are added or computed.
 *
 */
#include "Datum.h"
#include <list>
#include <string>
using namespace std;

class DatumStack {
public:
    DatumStack();
    DatumStack(Datum info[], int size);
    bool isEmpty();
    void clear();
    int size();
    Datum top();
    void pop();
    void push(Datum stuff);

private:
    std::list<Datum> stack;
};