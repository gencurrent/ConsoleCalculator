#include <iostream>
#include <stack>
#include <list>
#include <utility>
#include <algorithm>

using namespace std;

class Calculator{
    
    string m_expression;
    list<string> m_outList;
public:
    Calculator(){};
    Calculator(string &expression) : m_expression(expression){};
    
    
    
    bool isNumber(char c){
        return ((c >= '0' && c <= '9') || c == '.' || c == ',');
    }


    // Получить строку-число до тех пор, пока часть выражения является числом
    string getNumberInString(string::iterator &it){
        string number;
        
        if(*it == '-'){
            number.append(1, '-');
            it++;
        }
        while(isNumber(*it) && (it != m_expression.end())) {
            char a = *it;
            if(a == ',')
                a = '.';
            number.append(1, a);
            it++;
        }
        
        return number;
    }


    double calcExpression(){
        double result;
    }

    // Парсинг выражения
    double parseExpression(string &exp){
        this->m_expression = exp;
        
        //m_expression.erase( std::remove_if( m_expression.begin(), m_expression.end(), ::isspace ), m_expression.end() );
        
        double result;
        
        m_outList.clear();   // Список операндов и операторов
        stack<char> operStack;  // Стэк операторов
        
        for(string::iterator it = m_expression.begin(); it != m_expression.end() && *it != '\0'; it++){
            
            // Парсинг тех случаев, когда минус становится первым в начале выражения или внутри скобок
            if(*it == '('){
                operStack.push(*it);
                
                it++;
                
                if (*it == '-'){
                    m_outList.push_back(getNumberInString(it));
                }
                
            }
            
            if ((it == m_expression.begin()) && (*it == '-')){
                m_outList.push_back(getNumberInString(it));
                
            }
            
            
            if(isNumber(*it)){
                m_outList.push_back(getNumberInString(it));
            }
            
            if(*it == '+' || *it == '-'){
                operStack.push(*it);
                continue;
            }
            if(*it == '*' || *it == '/'){
                if(operStack.size() != 0){
                    // Смотрим на предыдущий оператор
                    char a = operStack.top();
                    // Если тоже оператор умножения или деления, выталкиваем предыдущий и помещаем в выходную строку
                    if(a == '*' || a == '/'){
                        m_outList.push_back(string(1, a));
                        operStack.pop();
                    }
                    
                }
                operStack.push(*it);
                
                continue;
            }
            
            
            
            if(*it == ')'){
                
                while(operStack.top() != '('){
                    m_outList.push_back(string(1, operStack.top()));
                    operStack.pop();
                }
                operStack.pop();    // Выталкиваем '('
                
                continue;
            }
            
            
            if(*it != ' '){
                string wrongString = "";
                while(!((isNumber(*it) || (*it == '*') || (*it == '/') || (*it == '+') || (*it == '-') || (*it == ' ') || (it == m_expression.end()) || (*it != '\0')))){
                    wrongString += *it;
                    it++;
                }
                if(wrongString.size() != 0){
                    cout << "Wrong input: " << wrongString << endl;
                    terminate();
                }
            }
        }
        
        // Выталкиваем операторы из стека
        while(!operStack.empty()){
            m_outList.push_back(string(1, operStack.top()));
            operStack.pop();
        }
        
        
        
        double locResult;
        // Считаем
        while(m_outList.size() != 1){
            pair<double, double> operands; 
            
            
            for(list<string>::iterator it = m_outList.begin(); it != m_outList.end(); it++){
                string str = *it;
                if(!str.compare("*")){
                    
                    operands = getOperands(it);
                    locResult = operands.first * operands.second;
                    
                    
                    string stringResult = doubleToString(locResult);
                    m_outList.insert(it, stringResult);
                    break;
                }
                
                if(!str.compare("/")){
                    operands = getOperands(it);
                    locResult = operands.first / operands.second;
                    
                    string stringResult = doubleToString(locResult);
                    m_outList.insert(it, stringResult);
                    break;
                }
                
                if(!str.compare("+")){
                    operands = getOperands(it);
                    locResult = operands.first + operands.second;
                    
                    string stringResult = doubleToString(locResult);
                    m_outList.insert(it, stringResult);
                    break;
                }
                
                if(!str.compare("-")){
                    operands = getOperands(it);
                    locResult = operands.first - operands.second;
                    
                    string stringResult = doubleToString(locResult);
                    m_outList.insert(it, stringResult);
                    
                    break;
                }
            }
            
        }
        
        result = stod(*m_outList.begin());
            
        
        return result;
    }
    
    pair<double, double> getOperands(list<string>::iterator &it){
        pair<double, double> operands;
        it--;
        operands.second = stod(*it);
        it--;
        operands.first = stod(*it);
                    
        it = m_outList.erase(it);
        it = m_outList.erase(it);
        it = m_outList.erase(it);
        
        return operands;
    }
    
    string doubleToString(double a){
        return to_string(a);
    }
    
};





int main(){
    string expression;
    
    std::getline(std::cin, expression);
    
    
    Calculator calc;
    
    cout << "Result = " << calc.parseExpression(expression) << endl;
    
    return 0;
}