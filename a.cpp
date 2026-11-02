#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <functional>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;

const double pi = 3.14159;
const double e = 2.718284;

/*
Приоритеты операций:
1. выражения в скобках ()
2. ^
3. * /
4. + -
5. ln sqrt sin cos итд
если приоритет операции ниже чем вершина стека то выталкиваем пока не будет иначе
*/

class Expression{
    std::string base;
    std::vector<std::string> polish;
    double res;

    unsigned char priority(const std::string& op){
        return (op=="^" || op == "sin" || op == "sqrt" || op=="cos" || op=="ln" || op=="!")? 3:(op=="*" || op == "/")? 2:(op=="+" || op == "-")? 1:0;
        // у ( нулевой приоритет
    }

    std::function<double(double,double)> convert_op2(const std::string& op) const {
        if (op == "+") return [](double a, double b) -> double {return a + b;};
        if (op == "-") return [](double a, double b) -> double {return a - b;};
        if (op == "/") return [](double a, double b) -> double {return a / b;};
        if (op == "*") return [](double a, double b) -> double {return a * b;};
        if (op == "^") return [](double a, double b) -> double {
            double res = (b>0)? a:1;
            while(b>0 && --b){res*=a;}while(b<=0 && b++){res/=a;}
            return res;
        };
        return nullptr;
    }
    std::function<double(double)> convert_op1(const std::string& op) const {
        if (op == "sin") return [](double a) -> double {return std::sin(a);};
        if (op == "cos") return [](double a) -> double {return std::cos(a);};
        if (op == "ln") return [](double a) -> double {return std::log(a);};
        if (op == "sqrt") return [](double a) -> double {return std::sqrt(a);};
        if (op == "!") return [](double a) -> double {double res=a;while(--a) res*=a;return res;};
        if (op == "arcsin") return [](double a) -> double {return std::asin(a);};
        if (op == "arccos") return [](double a) -> double {return std::acos(a);};
        if (op == "tg" || op == "tan") return [](double a) -> double {return std::tan(a);};
        return nullptr;
    }
    
    bool isoperation(const std::string& op){
        const std::string opers[] = {"+","-","*","/","^","(",")","ln","cos","sin","sqrt","!","arcsin","arccos","tg","tan"};
        for (const auto& x: opers) if (op==x) return true;
        return false;
    }

    void calc(){
        std::stack <double> st;
        for (const auto& x: polish){
            if (isdigit(x[0])) st.push(std::stod(x));
            else if (x == "pi") st.push(pi);
            else if (x == "e") st.push(e);
            else if (isalpha(x[0]) || x == "!"){
                double a = st.top(); st.pop();
                st.push(convert_op1(x)(a));
            }
            else {
                double b = st.top(); st.pop();
                double a = st.top(); st.pop();
                st.push(convert_op2(x)(a,b));
            }  
        }
        res = st.top();
    }
public:
    Expression(std::string& exp){
        base = std::move(exp);
        std::stack<std::string> st;
        for (int i = 0; i<base.size();){
            if (base[i] == ' ') {i++; continue;}
            if (isdigit(base[i])){
                
                std::string number; number.push_back(base[i++]);

                while(i < base.size() && (isdigit(base[i]) || base[i]=='.')) number.push_back(base[i++]);
                
                polish.push_back(number);
                continue;
            }
            if (!isdigit(base[i]) && base[i] != ' '){

                if (base[i] == 'p') {polish.push_back("pi");i+=2;continue;}
                if (base[i] == 'e') {polish.push_back("e");i++;continue;}

                std::string op; op.push_back(base[i++]);// +ln 1+ln(2)
                while (i < base.size() && !isdigit(base[i]) && !isoperation(op) && base[i]!='e' && base[i]!='p') op.push_back(base[i++]);
                if (!isoperation(op)) {
                    std::cerr<<"No such operation: "+op<<endl;
                    exit(-1);
                }
                if (op == "(") st.push(op);
                else if (op == ")"){
                    while (st.top() != "("){
                        polish.push_back(st.top()); st.pop();
                    }
                    st.pop();
                } else {
                    while (!st.empty() && (priority(st.top())>=priority(op))){
                        polish.push_back(st.top()); st.pop();
                    }
                    st.push(op);
                }
                continue;
            }
        }
        while (!st.empty()){
            polish.push_back(st.top());
            st.pop();
        }
        calc();
    }
    void print() const{
        cout<<"polish notation: ";
        for (auto& c: polish){
            cout<<c<<' ';
        }
        cout<<endl;
        cout<<"result: "<<res<<endl;
    }
    double getRes() const{
        return res;
    }
};
//объекты синхронизации c++
//мессенджер 
int main(){
    std::string exp;
    std::getline(cin, exp);
    Expression e(exp);
    e.print();
}