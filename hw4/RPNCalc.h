/*
 *  RPNCalc.h
 *  Arbert Xu (axu10)
 *  2/27/24
 *
 *  COMP 15 HW 4 CalcYouLater
 *
 *  This file creates the DatumStack class. It uses the parser function and 
 *  creates a datumStack. This class is a RPN calculator which takes in user 
 *  input and completes calculations. It creates a query where the user 
 *  inputs specific commands. 
 *
 */
#include "Datum.h"
#include "DatumStack.h"
#include "parser.h"
#include <string>
#include <iostream>
using namespace std;
class RPNCalc{
public:
    RPNCalc();
    ~RPNCalc();
    void run();
    void query(istream &input);
    bool got_int(string s, int *resultp);
    void Not();
    void swap();
    void doOperation(string command);
    void doBoolOperation(string command);
    void execute();
    void doFile();
    void doIf();
    void checkRStringForIf(int pop);
    void DoMath(string command, int first, int second);
    void DoBoolMath(string command, Datum first, Datum second);
private:
    DatumStack thaStack;
};