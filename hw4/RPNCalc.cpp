/*
 *  RPNCalc.cpp
 *  Arbert Xu (axu10)
 *  2/27/24
 *
 *  COMP 15 HW 4 CalcYouLater
 *
 *  This file initializes all of the functions for the RPNCalc class. It uses 
 *  a DatumStack to store inputs and complete different functions that the user
 *  inputs.
 *
 */

#include "RPNCalc.h"
#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include "parser.h"
#include <sstream>
using namespace std;

/* RPNCalc::RPNCalc()
Purpose: Constructs the RPNCalc. Initializes a DatumStack.
Parameters: n/a
Return: n/a
*/ 
RPNCalc::RPNCalc()
{

}

/* RPNCalc::RPNCalc()
Purpose: deconstructs the RPNCalc. Deconstructs the DatumStack.
Parameters: n/a
Return: n/a
*/ 
RPNCalc::~RPNCalc()
{

}

/* void RPNCalc::run()
Purpose: starts the query loop which takes in inputs from the user to do 
different commands. Outputs a message at the end of the loop.
Parameters: n/a
Return: n/a
*/ 
void RPNCalc::run()
{
    query(cin);
    cerr << "Thank you for using CalcYouLater.\n"; 
}

/* void RPNCalc::query(istream &input)
Purpose: Do a query loop which takes in user input and does different 
actions based on what the user inputs. Does not end until user enters quit or 
the inputs end.
Parameters: istream &input. Allows any form of input, be it a file or cin, to
be used in the query loop.
Return: n/a
*/ 
void RPNCalc::query(istream &input)
{
    int num;
    string command;
    while((input >> command) and (command != "quit")) //reads in command
    {
        if(command == "print") //will do print function. checks for errors
        {
            try
            {
                cout << thaStack.top().toString();
                cout << "\n";
            }
            catch(const std::exception& e)
            {
                std::cerr << "Error: " << e.what() << '\n';
            }
        }
        else if(command == "clear") //will do clear function.
        {
            thaStack.clear();
        } else if(got_int(command, &num)) //adds number Datum to DatumStack
        {
            Datum data(num);
            thaStack.push(data);
        } else if(command == "#t") // adds true Datum to DatumStack
        {
            Datum data(true);
            thaStack.push(data);
        } else if(command == "#f") // adds false Datum to DatumStack
        {
            Datum data(false);
            thaStack.push(data);
        } else if(command == "not") // not function. checks for errors
        {
            try
            {
                Not();
            }
            catch(const std::exception& e)
            {
                std::cerr << "Error: " << e.what() << '\n';
            }
        } else if(command == "drop") // pops element. checks for errors.
        {
            try
            {
                thaStack.pop();
            }
            catch(const std::exception& e)
            {
                std::cerr << "Error: " << e.what() << '\n';
            }
        } else if (command == "swap") // swaps front two elements. check errors
        {
            try
            {
                swap();
            }
            catch(const std::runtime_error &e)
            {
                cerr << "Error: empty_stack\n";
            }
        } else if (command == "dup") // duplicates front element. checks errors
        {
            try
            {
                thaStack.push(thaStack.top());
            }
            catch(const std::exception& e)
            {
                std::cerr << "Error: " << e.what() << '\n';
            }
        }
        else if (command == "<" or (command == ">") or (command == "<=") or
        (command == ">=") or (command == "==")) // does bool operations
        { //checks for errors
            try
            {
                doBoolOperation(command);
            }
            catch(const std::runtime_error &e)
            {
                std::cerr << "Error: " << e.what() << '\n';
            }
        } else if (command == ("+") or (command == "-") or (command == "*") 
        or (command == "/") or (command == "mod")) // does math operations
        { // checks for errors
            try
            {
                doOperation(command);
            }
            catch(const std::runtime_error &e)
            {
                std::cerr << "Error: " << e.what() << '\n';
            }
        } else if (command[0] == '{') // will parse string
        {
            string pString;
            pString = parseRString(input);
            Datum pData(pString);
            thaStack.push(pData);
        } else if (command == "exec") // will execute RString. checks errors
        {
            try
            {
                execute();
            }
            catch(const std::exception& e)
            {
                std::cerr << "Error: " << e.what() << '\n';
            }
            
            
        } else if (command == "file") // will execute file. checks errors
        {
            try
            {
                doFile();
            }
            catch(const std::exception& e)
            {
                std::cerr << "Error: " << e.what() << '\n';
            }
            
            
        } else if (command == "if") // will take 3 Datums and choose one based
        { // on whether the third datum is true or false.
            try
            {
                doIf();
            }
            catch(const std::exception& e)
            {
                std::cerr << "Error: " << e.what() << '\n';
            }
        } else 
        {
            std::cerr << command << ": unimplemented\n";
        }
    }
}
/* void bool RPNCalc::got_int(string s, int *resultp)
Purpose: Takes a string and will see if it is an number that can be an int
Parameters: string s, int *resultp. A string to read and an int pointer to 
return a value to if the string is a number.
Return: bool true/false if string can be an int, and if true, an int to the 
pointer.
*/ 
bool RPNCalc::got_int(string s, int *resultp)
{
        /* Holds the first non-whitespace character after the integer */
        char extra;

        return sscanf(s.c_str(), " %d %c", resultp, &extra) == 1;
}

/* void RPNCalc::Not()
Purpose: If top Datum is a boolean, will return the opposite of that bool.
If top is not a boolean, will cerr an error message and pop that Datum.
Parameters: N/A
Return: N/A
*/ 
void RPNCalc::Not()
{
    try
    {
        if(thaStack.top().getBool()) // if datum is true, will push a false 
        {
            Datum data(false);
            thaStack.pop();
            thaStack.push(data);
        } else // will push a true datum
        {
            Datum data(true); 
            thaStack.pop();
            thaStack.push(data);
        }
    }
    catch(const std::exception& e)
    {
        thaStack.pop();
        std::cerr << "Error: " << e.what() << '\n'; 
    }
    return;
}

/* void RPNCalc::swap()
Purpose: Will swap the top two Datums on the stack with each other. The top 
Datum will swap with the second Datum. Will cerr an error message if not 
enough elements in DatumStack. 
Parameters: N/A
Return: N/A
*/ 
void RPNCalc::swap()
{
    Datum thaTop = thaStack.top();
    thaStack.pop();
    Datum thaSecond = thaStack.top();
    thaStack.pop();
    thaStack.push(thaTop); // makes it so it is now second from top
    thaStack.push(thaSecond); //makes previous second now top of stack
    return;
}

/* void RPNCalc::doOperation(string command)
Purpose: checks to see if the top two Datums are integers. Will cerr error 
message if that is not the case. If top two Datums are integers, will call
DoMath function which will do the actual math.
Parameters: string command. String of the math operation. will be used in 
DoMath function.
Return: N/A
*/ 
void RPNCalc::doOperation(string command)
{
    int successes = 0; // sees how many successful ints there are
    try
    {
        int first = thaStack.top().getInt();
        thaStack.pop();
        successes++;
        int second = thaStack.top().getInt();
        thaStack.pop();
        DoMath(command, first, second); // does actual math operation
    }
    catch(const std::exception& e)
    {
        if(successes == 0) // if zero successes, pops both datums
        {
            thaStack.pop();
            thaStack.pop();
        } else if (successes == 1)
        {
            thaStack.pop(); // if 1 success then pop 1 element
        }
        std::cerr << "Error: " << e.what() << '\n';
    }
}

/* void RPNCalc::DoMath(string command, int first, int second)
Purpose: Does math operation based on the string command. If +, will add. 
If - will subtract. etc. Will check if dividing/mod by zero. pushes answer
onto DatumStack.
Parameters: string command which is the operator. int second which is the 
number that comes first in equation, and int first which is number that comes 
second in equation.
Return: N/A
*/ 
void RPNCalc::DoMath(string command, int first, int second)
{
    int answer = 0;
    if(command == "+")
    {
        answer = (second) + (first);
        Datum thaAnswer(answer);
        thaStack.push(thaAnswer);
    } else if (command == "-") {
        answer = (second) - (first);
        Datum thaAnswer(answer);
        thaStack.push(thaAnswer);
    } else if (command == "*") {
        answer = (second) * (first);
        Datum thaAnswer(answer);
        thaStack.push(thaAnswer);
    } else if (command == "/") {
        if(first == 0) // checks if dividng by zero
        {
            std::cerr << "Error: division by 0.\n";
            return;
        }
        answer = (second) / (first);
        Datum thaAnswer(answer);
        thaStack.push(thaAnswer);
    } else {
        if(first == 0) // checks if mod by zero
        {
            std::cerr << "Error: division by 0.\n";
            return;
        }
        answer = (second) % (first);
        Datum thaAnswer(answer);
        thaStack.push(thaAnswer);
    }
}

/* void RPNCalc::doBoolOperation(string command)
Purpose: Checks if top two elements are integers. If they are, will send the 
Datums to DoBoolMath function which will do bool operation.
Parameters: string command which is the bool operator which will be used by 
DoBoolMath.
Return: N/A
*/ 
void RPNCalc::doBoolOperation(string command)
{
    int successes = 0; // number of successful bools there are
    try
    {
        int first = thaStack.top().getInt();
        successes++;
        int second = thaStack.top().getInt();
        successes++;
        Datum firstD = thaStack.top();
        thaStack.pop();
        Datum secondD = thaStack.top();
        thaStack.pop();
        DoBoolMath(command, firstD, secondD); // does bool operations
    }
    catch(const std::exception& e)
    {
        if(successes == 0) //if zero successes, pop both elements
        {
            thaStack.pop();
            thaStack.pop();
        } else if (successes == 1) // if one success, pop one element
        {
            thaStack.pop();
        }
        std::cerr << "Error: " << e.what() << '\n';
    }
}

/* void RPNCalc::DoBoolMath(string command, Datum first, Datum second)
Purpose: Does bool operation from command. The datum second will do bool 
operation on datum first. If bool is <, then it will be Datum second < 
Datum first. Will push true or false Datum onto the stack.
Parameters: string command, Datum first, Datum second. Command will be the 
bool operator, Datum first will be second Datum in equation, Datum second 
will be first Datum in equation.
Return: N/A
*/ 
void RPNCalc::DoBoolMath(string command, Datum first, Datum second)
{
    bool answer;
    if(command == "<")
    {
        answer = second.operator<(first);
        Datum thaAnswer(answer);
        thaStack.push(thaAnswer);
    } else if (command == ">") {
        answer = not(second.operator<(first));
        Datum thaAnswer(answer);
        thaStack.push(thaAnswer);
    } else if (command == "<=") {
        
        answer = ((second.operator==(first)) or (second.operator<(first)));
        Datum thaAnswer(answer);
        thaStack.push(thaAnswer);
    } else if (command == ">=") {
        answer = (not(second.operator<(first)) or second.operator==(first));
        Datum thaAnswer(answer);
        thaStack.push(thaAnswer);
    } else {
        answer = second.operator==(first);
        Datum thaAnswer(answer);
        thaStack.push(thaAnswer);
    }
}

/* void RPNCalc::execute()
Purpose: Will execute the actions inside of a RString. If the top Datum
of the DatumSTack is not a RString, will cerr and error and pop that 
element. SEnds the instructions inside the RString into the query.
Parameters: N/A
Return: N/A
*/ 
void RPNCalc::execute()
{
    try
    {
        string action = thaStack.top().getRString();
        action[0] = ' ';
        action[action.length() - 1] = ' ';
        thaStack.pop();
        // puts string of commands in RString into a stream to be read in query
        istringstream inputs(action); 
        query(inputs);
    }
    catch(const std::exception& e)
    {
        thaStack.pop();
        std::cerr << "Error: cannot execute non rstring" << '\n';
    }
}

/* void RPNCalc::doFile()
Purpose: Will read the file inside the top element RString and add all 
instructions to the query loop. If top element is not a RString, will cerr
an error message and pop the element.
Parameters: N/A
Return: N/A
*/ 
void RPNCalc::doFile()
{
    try
    {
        string rString = thaStack.top().getRString();
        thaStack.pop();
        rString.erase(0, 2);
        rString.erase(rString.length() - 2, 2);
        ifstream instream;
        instream.open(rString);
        if (not instream.is_open())
        {
            cerr << "Unable to read " << rString << endl;
        }
        if(instream.is_open())
        {
            query(instream);
        }
    }
    catch(const std::exception& e)
    {
        thaStack.pop();
        std::cerr << "Error: file operand not rstring"  << '\n';
    }
}

/* void RPNCalc::doIf()
Purpose: Will do if function. Will take top three elements off of the 
DatumStack. The top two must be RStrings and the 3rd element must be a 
boolean Datum. If the boolean is false, The top RSTring will be executed. If 
the boolean is true, the second RString will be executed. Will cerr errors 
if the Datums do not match the required ones. 
Parameters: N/A
Return: N/A
*/ 
void RPNCalc::doIf()
{
    // pops three elements if first element is not RString
    checkRStringForIf(3);
    Datum f = thaStack.top();
    thaStack.pop();
    // pops two elements if second element is not RString
    checkRStringForIf(2);
    Datum t = thaStack.top();
    thaStack.pop();
    if(not thaStack.top().isBool())
    {
        thaStack.pop();
        throw std::runtime_error("Error: expected boolean in if test");
    }
    Datum decide = thaStack.top();
    thaStack.pop();
    if(decide.getBool())
    {
        thaStack.push(t);
        execute();
    } else 
    {
        thaStack.push(f);
        execute();
    }
}

/* void RPNCalc::checkRStringForIf(int pop)
Purpose: Checks if the top element is a RString. If it is not, will pop the 
number of elements needed to pop depending on if Datum is the first or second 
RString taken in. Will also throw error.
Parameters: int pop. Number of elements that need to be popped.
Return: N/A
*/ 
void RPNCalc::checkRStringForIf(int pop)
{
    if(not thaStack.top().isRString())
    {
        for(int i = 0; i < pop; i++)
        {
            thaStack.pop();
        }
        throw std::runtime_error("expected rstring in if branch");
    }
}