#include <bits/stdc++.h>

using namespace std;


typedef int Elem;

class CNode{
private:
    Elem elem;
    CNode* next;
    friend class CircleList;
};

class CircleList{
public:
    CircleList();
    ~CircleList();
    bool empty() const;
    const Elem& front() const;
    const Elem& back() const;
    void advance();
    void add(const Elem& e);
    void remove();
private:
    CNode* cursor;
};

CircleList::CircleList():cursor(NULL) {} // 생성자
CircleList::~CircleList(){              //소멸자
    while(!empty()) remove();
}
bool CircleList::empty() const{      // 비었는지?
    return cursor == nullptr;
}
const Elem& CircleList::back() const{ // cursor 출력
    return cursor->elem;
}
const Elem& CircleList::front() const{ // cursor 뒤의 원소 출력
    return cursor->next->elem;
}
void CircleList::advance(){ // cursor 증가
    cursor = cursor->next;
}
void CircleList::add(const Elem&e){ // cursor뒤에 원소추가
    CNode* v = new CNode;           // 새 노드 생성
    v->elem = e;
    if(cursor == nullptr){          //리스트가 비었는지?
        v->next = v;                // 자신을 가르킨다.
        cursor = v;                 // cursor가 v를 가르킨다.
    }else{
        v->next = cursor->next;     // cursor뒤에 v를 link in 한다.
        cursor->next = v;
    }
}

void CircleList::remove(){
    CNode* old = cursor->next;
    if(old==cursor) cursor = nullptr;
    else cursor->next = old->next;
    delete old;
}


int main(){
    CircleList CL;
    CL.add(5);
    cout << CL.front();
}