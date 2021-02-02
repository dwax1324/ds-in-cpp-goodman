#include <bits/stdc++.h>
// using namespace std;

typedef int Elem;

struct Node{
    Elem elem;
    Node* prev;
    Node* next;
};

class Iterator{     // 리스트 이터레이터
public:
    Elem& operator*(); // 원소에 대한 레퍼런스
    bool operator==(const Iterator&p) const; // 위치 비교
    bool operator!=(const Iterator&p) const;
    Iterator& operator++();     // 다음 위치로 이동
    Iterator& operator--();     // 이전 위치로 이동
    friend class NodeList;      // NodeList에 접근 허용
// private:
    Node* v;            // 노드에 대한 포인터
    Iterator(Node* u);  // 노드로 부터 만듬
};

class NodeList{
private:
    Node(); 
    class Iterator;
public:
public:
    NodeList();
    int size() const;
    bool empty() const;
    Iterator begin() const;
    Iterator end() const;
    void insertFront(const Elem&e);
    void insertBack(const Elem&e);
    void insert(const Iterator& p, const Elem&e);
    void eraseFront();
    void eraseBack();
    void erase(const Iterator& p);
private:
    int n;
    Node* header;
    Node* trailer;
};

NodeList::Iterator::Iterator(Node* u){
    v=u;
}

Elem& NodeList::Iterator::operator*(){
    return v->elem;
}

bool NodeList::Iterator::operator==(const Iterator& p)const{
    return v == p.v;
}

bool NodeList::Iterator::operator!=(const Iterator& p) const{
    return v!=p.v;
}
NodeList::Iterator& NodeList::Iterator::operator++(){
    v = v->next; 
    return *this;
}

NodeList::Iterator& NodeList::Iterator::operator--(){
    v = v->prev;
    return *this;
}

NodeList::NodeList(){
    n=0;
    header=  new Node;
    trailer = new Node;
    header->next = trailer;
    trailer->prev = header;
}

int NodeList::size() const { 
    return n;
}
bool NodeList::empty() const {
    return (n ==0);
}
NodeList::Iterator NodeList::begin() const{
    return Iterator(header->next);
}

NodeList::Iterator NodeList::end() const{
    return Iterator(trailer);
}

void NodeList::insert(const NodeList::Iterator&p , const Elem& e){
    Node*w = p.v;
    Node*u = w->prev;
    Node*v = new Node;
    v->elem = e;
    v->next = w; w-> prev = v;
    v->prev= u; u->next = v;
    n++;
}

void NodeList::insertFront(const Elem&e){
    insert(begin(),e);
}

void NodeList::insertBack(const Elem&e){
    insert(end(),e);
}

void NodeList::erase(const Iterator& p){
    Node* v = p.v;
    Node* w = v->next;
    Node* u = v->prev;
    u->next = v->prev;
    u->next = w; w->prev = u;
    delete v;
    n--;
}
void NodeList::eraseFront(){
    erase(begin());
}

void NodeList::eraseBack(){
    erase(--end());
}

NodeList::Iterator::Iterator(Node* u){}

private:


}