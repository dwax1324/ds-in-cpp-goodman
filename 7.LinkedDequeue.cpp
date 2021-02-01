#include <bits/stdc++.h>

using namespace std;

typedef int Elem;

class LinkedDequeue{

public:
    LinkedDequeue();
    int size() const;
    bool empty() const;
    const Elem& front() const;
    const Elem& back() const;
    void insertFront(const Elem&e);
    void insertBack(const Elem&e);
    void removeFront();
    void removeBack();
private:
    list<Elem>D;
    int n;
};

LinkedDequeue::LinkedDequeue(): n(0){}

const Elem& LinkedDequeue::front() const{
    if(empty()) throw invalid_argument("front error");
    return D.front();
}

const Elem& LinkedDequeue::back() const{
    if(empty()) throw invalid_argument("back error");
    return D.back();
}

bool LinkedDequeue::empty() const{
    return n==0;
}

int LinkedDequeue::size() const{
    return n;
}

void LinkedDequeue::insertFront(const Elem&e){
    D.push_front(e);
    n++;
}

void LinkedDequeue::insertBack(const Elem&e){
    D.push_back(e);
    n++;
}

void LinkedDequeue::removeFront(){
    if(empty()) throw invalid_argument("removeFront error");
    D.pop_front();
    n--;
}

void LinkedDequeue::removeBack(){
    if(empty()) throw invalid_argument("removeBack error");
    D.pop_back();
    n--;
}

int main(){
    LinkedDequeue LDQ;
    for(int i=0; i < 10; i++) LDQ.insertBack(i);
    for(int i=0; i < 10; i++) {
        cout << LDQ.back() << ' ';
        LDQ.removeBack();
    }   
}