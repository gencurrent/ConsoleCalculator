#include <iostream>
#include <stack>
#include <list>
#include <vector>
#include <utility>
#include <algorithm>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "calculator.hpp"

//#define DEBUG

using namespace std;


    Calculator calc;
    // Вектор выражений для тестирования
    vector<pair<string, double> > exps = {
        {"-1 + 5 - 3", 1},
        {"- 10 + (8 * 2.5) - (3 / 1,5)", 8},
        {"1 + (2 * (2.5 + 2.5 + (3 - 2))) - (3 / 1.5)", 11},
        {"99 * 115 / 1 , 5", 8},
        {"7*2-10000", 10000-14},
    };

    TEST_CASE( "Testing", "[expression]" ) {
        vector<pair<string, double> >::iterator it;
        for(it = exps.begin(); it != exps.end(); it++){
            INFO("Wrong answer!\tExpression: " << it->first << ' ' << "Answer: " << it->second);
            REQUIRE( calc.parseExpression(it->first) == it->second );
        }
            
    }
