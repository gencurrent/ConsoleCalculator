#include <iostream>
#include <stack>
#include <list>
#include <vector>
#include <utility>
#include <algorithm>

// Определение в случае необходимости вывода некоторых дебаговых ситуаций
//#define DEBUG

using namespace std;

class Calculator{
    
    string m_expression;
    list<string> m_outList;
    stack<char> m_operStack;  // Стэк операторов
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
        it--;
        
        return number;
    }


    double calcExpression(){
        double result;
    }
    
    void parseSubExpression(string::iterator &it){
        
        
        for(; (it != m_expression.end()) && (*it != '\0'); it++){
            
            // Парсинг тех случаев, когда минус становится первым в начале выражения или внутри скобок
            if(*it == '('){
                m_operStack.push(*it);
                
                
                if (*(it + 1) == '-'){
                    it++;
                    
                    m_outList.push_back(getNumberInString(it));
                }
                continue;
            }
            
            if ((it == m_expression.begin()) && (*it == '-')){
                m_outList.push_back(getNumberInString(it));
                continue;
            }
            
            
            if(isNumber(*it)){
                m_outList.push_back(getNumberInString(it));
            }
            
            if(*it == '+' || *it == '-'){
                m_operStack.push(*it);
                continue;
            }
            if(*it == '*' || *it == '/'){
                if(m_operStack.size() != 0){
                    // Смотрим на предыдущий оператор
                    char a = m_operStack.top();
                    // Если тоже оператор умножения или деления, выталкиваем предыдущий и помещаем в выходную строку
                    if(a == '*' || a == '/'){
                        m_outList.push_back(string(1, a));
                        m_operStack.pop();
                    }
                    
                }
                m_operStack.push(*it);
                
                continue;
            }
            
            
            
            if(*it == ')'){
                
                while(m_operStack.top() != '('){
                    m_outList.push_back(string(1, m_operStack.top()));
                    m_operStack.pop();
                }
                m_operStack.pop();    // Выталкиваем '('
                
                continue;
            }
            
            
            
            if(*it != ' '){
                string wrongString;
                while(!(  
                            (isNumber(*it)) || 
                            (*it == '*') || (*it == '/') || 
                            (*it == '+') || (*it == '-') || 
                            (*it == ' ') || (*it == '(') || 
                            (*it == ')') 
                       ) && 
                       (it != m_expression.end()) && (*it != '\0')
                     )  {
                    wrongString += *it;
                    it++;
                }
                if(wrongString.length() != 0){
                    cout << "Wrong input: " << wrongString << endl;
                    terminate();
                }
            }
            
        }
    }

    double parseExpression(string &exp){
        this->m_expression = exp;
        
        return parseExpression();
    }
    
    // Парсинг выражения
    double parseExpression(){
        
        // Удаление ненужных символов
        m_expression.erase(std::remove_if( m_expression.begin(), m_expression.end(), 
            [](char c){ return (c =='\r' || c =='\t' || c == ' ' || c == '\n');}), m_expression.end() );
        
        // Очистка списка операндов и операторов
        m_outList.clear();   
        // Очищаем стек операторов
        while(!m_operStack.empty())
            m_operStack.pop();
        
        double result;
        string::iterator it = m_expression.begin();
        
        parseSubExpression(it);
        
        
        
        
        // Выталкиваем операторы из стека
        while(!m_operStack.empty()){
            m_outList.push_back(string(1, m_operStack.top()));
            m_operStack.pop();
        }
        
        
#ifdef DEBUG
        cout << "OutPut String dump\n" ;
        for(list<string>::iterator it = m_outList.begin(); it != m_outList.end(); it++)
            cout << *it << ' ';
        cout << "\nEnd of dumping\n";
#endif
        
        
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