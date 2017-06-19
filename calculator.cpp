#include <iostream>
#include <stack>
#include <list>
#include <utility>
#include <algorithm>



#include "catch.hpp"

//#define DEBUG
#include "calculator.hpp"


using namespace std;


int main(){
    string expression;
    
    
    
    Calculator calc;
    
    do{
        (std::getline(std::cin, expression));
        if(expression == "q")
            break;
        cout << "Result = " << calc.parseExpression(expression) << endl;
    }while(true);
    
    return 0;
}