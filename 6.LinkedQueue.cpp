#include <bits/stdc++.h>
using namespace std;

typedef int Elem;


// 환형리스트 가져옴
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

/// 큐클래스 시작
class LinkedQueue{
public:
    LinkedQueue();
    int size() const;
    bool empty() const;
    const Elem& front();
    void enqueue(const Elem&e);
    void dequeue();
private:
    CircleList C;       //환형리스트
    int n;              //원소의 갯수
};
LinkedQueue::LinkedQueue():C(),n(0){}
int LinkedQueue::size() const{
    return n;
}

bool LinkedQueue::empty() const{
    return n==0;
}
const Elem& LinkedQueue::front(){
    if(empty()) throw invalid_argument("front error: queue is empty");
    return C.front();
}
void LinkedQueue::enqueue(const Elem&e){
    C.add(e);
    C.advance();
    n++;
}

void LinkedQueue::dequeue() {
    if(empty()) throw invalid_argument("dequeue error: queue is empty");
    C.remove();
    n--;
}


int main(){
    LinkedQueue LQ;
    for(int i=0; i < 10; i++) LQ.enqueue(i);
    while(LQ.size()){
        cout << LQ.front() << " ";
        LQ.dequeue();
    }
}