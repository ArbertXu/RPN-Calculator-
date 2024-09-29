/*
Main.cpp
Arbert Xu (axu10)
2/28/2024
COMP 15 HW 4 CalcYouLater
This creates the calculator and runs it.
*/
#include "parser.h"
#include "RPNCalc.h"
#include <string>
#include <iostream>
#include <fstream>
int main(int argc, char *argv[])
{
    RPNCalc calculator;
    calculator.run();
    return 0;
}