#include <bits/stdc++.h>

using namespace std;

typedef int Elem;

class LinkedStack{
public:
    LinkedStack();
    int size() const;
    bool empty() const;
    const Elem& top() const;
    void push(const Elem& e);
    void pop();
private:
    list<Elem> S; // 연결리스트(STL)
    int n;        // 들어있는 개수
};

LinkedStack::LinkedStack():S(),n(0){}  // 생성자
int LinkedStack::size() const{
    return n;
}
bool LinkedStack::empty() const{
    return n == 0;
}
const Elem& LinkedStack::top() const{
    if(empty()) throw invalid_argument("top error: stack is empty");
    return S.front();
}
void LinkedStack::push(const Elem&e){
    ++n;
    S.push_front(e);
}
void LinkedStack::pop() {
    if(empty()) throw invalid_argument("pop error: stack is empty");
    --n;
    S.pop_front();
}


int main(){
    LinkedStack LS;
    for(int i=0; i < 10; i++) LS.push(i);
    while(LS.size()){
        cout << LS.top() << " ";
        LS.pop();
    }
}