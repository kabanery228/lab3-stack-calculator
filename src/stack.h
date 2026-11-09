#define STACK_H

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