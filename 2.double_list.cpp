#include <bits/stdc++.h>
using namespace std;


typedef int Elem; // 리스트 원소 자료형

class DNode{
private:
    Elem elem;              // 노드 값
    DNode* prev;            // 이전 노드 포인터
    DNode* next;            // 다음 노드 포인터
    friend class DLinkedList;// DLinkedList의 접근을 허용(friend)
};


class DLinkedList{
public:
    DLinkedList();                  //생성자
    ~DLinkedList();                 //소멸자
    bool empty() const;             // 비었는지?
    const Elem& front() const;      // 맨앞원소접근
    const Elem& back() const;       // 맨뒤원소접근
    void addFront(const Elem& e);   // 맨앞원소에 삽입
    void addBack(const Elem&e);     // 맨뒤원소에 삽입
    void removeFront();             // 맨앞원소 삭제
    void removeBack();              // 맨뒤원소 삭제
private:
    DNode* header;                  // 리스트 보초병
    DNode* trailer;
protected:                             // 지역 유틸
    void add(DNode* v, const Elem& e); // v노드 이전에 삽입한다.
    void remove(DNode* v);             // v노드를 삭제한다.
};

DLinkedList::DLinkedList(){             // 생성자
    header = new DNode;                 // 보초병생성
    trailer = new DNode;
    header->next = trailer;             // 서로를 마주보게함
    trailer->prev = header;
}

DLinkedList::~DLinkedList(){            // 소멸자
    while(!empty()) removeFront();      // 보초병 제외 모든 노드 삭제
    delete header;                      // 보초병 삭제
    delete trailer;
}
bool DLinkedList:: empty() const{       
    return (header->next == trailer);
}
const Elem& DLinkedList::back() const{
    return trailer->prev->elem;
}
const Elem& DLinkedList::front() const{
   return header->next->elem;
}

void DLinkedList::add(DNode* v, const Elem& e){ // v이전에 끼워넣기
    DNode* u = new DNode; u->elem = e;          // e이전에 새로운 노드 u를 만들고 값을 준다
    u->next = v;                                // u의 next는 v를 가르킨다.
    u->prev = v->prev;                          // u의 prev는 v의 prev다.
    v->prev->next = v->prev = u;                // v의 이전노드와 v사이에 u를 끼워넣는다.
}

void DLinkedList::addFront(const Elem& e){
    add(header->next, e);
}

void DLinkedList::addBack(const Elem& e){
    add(trailer,e);
}

void DLinkedList::remove(DNode* v){ // remove node v
    DNode*u = v->prev;              // predecessor (앞노드)
    DNode*w = v->next;              // successor (뒷노드)
    u->next = w;                    // v를 리스트로부터 unlink
    w->prev = u;
    delete v;
}

void DLinkedList::removeFront(){
    remove(header->next);
}

void DLinkedList::removeBack(){
    remove(trailer->prev);
}


int main(){
    DLinkedList dk;
    for(int i=0; i < 10; i++) dk.addFront(3);
    cout << dk.empty();
}