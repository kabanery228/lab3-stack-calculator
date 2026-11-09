#include "calculator.h"

int main(){
    std::string exp;
    std::getline(cin, exp);
    Expression e(exp);
    e.print();
    e.calc({ 2 });
    cout << e.getRes();
}