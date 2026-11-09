#include <iostream>
#include <string>
//#include <stack>
#include <vector>
#include <functional>
#include <cmath>
#include <map>

using std::cin;
using std::cout;
using std::endl;

const double pi = 3.14159;
const double e = 2.718282;

/*
Приоритеты операций:
1. выражения в скобках ()
2. ^
3. * /
4. + -
5. ln sqrt sin cos итд
если приоритет операции ниже чем вершина стека то выталкиваем пока не будет иначе
*/
template<class T>
class stack {
    size_t sz = 1000;
    T* pMem;
    int tp = -1;
public:
    stack<T>() :pMem(new T[sz]) {};
    void push(const T& val) {
        pMem[++tp] = val;
    }
    T top()  {
        return pMem[tp];
    }
    void pop() {
        tp--;
    }
    bool empty() {
        return tp < 0;
    }
    ~stack() {
        delete[] pMem;
    }
};

class Expression{
    std::string base;
    std::vector<std::string> polish;
    double res = -1;
    std::map <std::string, double> operands;
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

    bool isunary(const std::string& op) {
        return op == "ln" || op == "cos" || op == "sin" || op == "sqrt" ||
            op == "!" || op == "arcsin" || op == "arccos" ||
            op == "tg" || op == "tan";
    }


    void parse() {
        stack<std::string> st;
        for (int i = 0; i < base.size();) {
            if (base[i] == ' ') { i++; continue; }
            if (isdigit(base[i])) {

                std::string number; number.push_back(base[i++]);

                while (i < base.size() && (isdigit(base[i]) || base[i] == '.')) number.push_back(base[i++]);

                polish.push_back(number);
                continue;
            }
            if (!isdigit(base[i]) && base[i] != ' ') {

                if (base[i] == 'p') { polish.push_back("pi");i += 2;continue; }
                if (base[i] == 'e') { polish.push_back("e");i++;continue; }

                std::string op; op.push_back(base[i++]);// +ln 1+ln(2)
                while (i < base.size() && !isdigit(base[i]) && !isoperation(op) && base[i] != 'e' && base[i] != 'p' && base[i]!=' ') op.push_back(base[i++]);
                if (!isoperation(op)) {
                    operands[op] = 0.0;
                    polish.push_back(op);
                    continue;
                }
                if (op == "(") st.push(op);
                else if (op == ")") {
                    while (st.top() != "(") {
                        polish.push_back(st.top()); st.pop();
                    }
                    st.pop();
                }
                else {
                    while (!st.empty() && (priority(st.top()) >= priority(op))) {
                        polish.push_back(st.top()); st.pop();
                    }
                    st.push(op);
                }
                continue;
            }
        }
        while (!st.empty()) {
            polish.push_back(st.top());
            st.pop();
        }
    }
public:
    Expression(std::string& exp){
        base = std::move(exp);
        stack<std::string> st;
        parse();
        //calc();
    }
    void calc(const std::vector<double>& values) {
        size_t i = 0;
        for (auto& x : operands) x.second = values[i++];
        stack<double> st;
        for (const auto& x : polish) {
            if (isdigit(x[0])) st.push(std::stod(x));
            else if (x == "pi") st.push(pi);
            else if (x == "e") st.push(e);
            else if (!isoperation(x)) st.push(operands[x]);
            else if (isunary(x)) {
                double a = st.top(); st.pop();
                st.push(convert_op1(x)(a));
            }
            else {
                double b = st.top(); st.pop();
                double a = st.top(); st.pop();
                st.push(convert_op2(x)(a, b));
            }
        }
        res = st.top();
    }
    void print() const {
        //for (const auto& x : operands) {
        //    cout << x.first << ' ' << x.second << endl;
        //}
        cout<<"polish notation: ";
        for (auto& c: polish){
            cout<<c<<' ';
        }
        cout<<endl;
        //cout<<"result: "<<res<<endl;
    }
    double getRes() const{
        return res;
    }
};

int main(){
    std::string exp;
    std::getline(cin, exp);
    Expression e(exp);
    e.print();
    e.calc({ 1,2 });
    cout << e.getRes();
}