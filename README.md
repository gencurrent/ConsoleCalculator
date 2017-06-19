# ConsoleCalculator

An RPN console calculator that takes into account parntheses. 

The symbols it works with are: 
* '+'
* '-'
* '*'
* '/'
* '('
* ')'
* ' ' (space)
* '0' - '9'
* ',' (seen as '.')
* '.'


catch.hpp - libraty for unit-testing

calculator.cpp - main program 

calculator.hpp - main header file to include 

calculator_test.cpp - main program for unit-testing


To compile with g++:

g++ -std=c++11 -o calc calculator.cpp

g++ -std=c++11 -o calc_test calculator_test.cpp
