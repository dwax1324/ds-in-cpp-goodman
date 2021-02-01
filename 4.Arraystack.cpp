#include <bits/stdc++.h>
using namespace std;


template <typename E>
class ArrayStack{
    enum { DEF_CAPACITY = 100 };        // 기본 스택 용량
public:
    ArrayStack(int cap = DEF_CAPACITY); // 생성자: 기본용량
    int size() const;                    
    bool empty() const;
    const E& top() const ;
    void push(const E& e) ;
    void pop() ;
private:
    E* S;           // 스택 배열
    int capacity;   // 스택 배열 용량
    int t;          // 스택의 top을 가르킴
};

template <typename E>
ArrayStack<E>::ArrayStack(int cap):S(new E[cap]),capacity(cap),t(-1){}
template <typename E>
int ArrayStack<E>::size() const{
    return (t+1);    // 아이템의 갯수, top+1
}
template <typename E>
bool ArrayStack<E>::empty() const{
    return (t<0) ;   // 스택이 비었는지
}
template <typename E>
const E& ArrayStack<E>::top() const {
    if(empty()) throw invalid_argument("top error: Stack is empty");
    return S[t];
}
template <typename E>
void ArrayStack<E>::push(const E&e){
    if(size()==capacity) throw invalid_argument("push error: Stack is full");
    S[++t] = e;
}

template <typename E>
void ArrayStack<E>::pop() {
    if(empty()) throw invalid_argument("pop error: empty stack");
    --t;
}


int main(){
    ArrayStack<int>stk;
    for(int i=0; i < 10; i++) stk.push(i);
    while(stk.size()) {
        cout << stk.top() << ' ';
        stk.pop();
    }
}