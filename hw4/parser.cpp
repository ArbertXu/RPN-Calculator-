/*
 *  parser.cpp
 *  Arbert Xu (axu10)
 *  2/27/24
 *
 *  COMP 15 HW 4 CalcYouLater
 *
 *  This file initializes the parseRString function. It is used by RPNCalc 
 *  to read in different RStrings to compute.
 *
 */

#include <string>
#include <iostream>
using namespace std;


/* string parseRString(istream &input)
Purpose: reads in a RString as input and reads all parts of the RString until
all {} are closed or until the input is over.
Parameters: istream &input. Takes an input and will keep reading in inputs 
until the inputs are finished or until all { brackets are closed.
Return: a complete string of the input
*/ 
string parseRString(istream &input) 
{
    string in;
    bool end = true;
    int num = 1; // string starts out with 1 {.
    string parsedString = "{";
    while((not input.eof()) and (end))
    {
        input >> in;
        if(in != " ")
        {
            parsedString += " ";
            parsedString += in;
        }
        if(in == "{")
        {
            num++;
        }
        if(in == "}")
        {
            num--;
        }
        if(num == 0)
        {
            end = false;
        }
    }
    return parsedString;
}
