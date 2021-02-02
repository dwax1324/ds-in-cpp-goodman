#include <bits/stdc++.h>

using namespace std;

template <typename E>

class SNode{
public:
    E elem;
    SNode<E>* next;
    
    // friend class SLinkedList<E>;  // provide SLinekedList access
};

template <typename E>
class SLinkedList{
public:
    SLinkedList();
    ~SLinkedList();
    bool empty() const; // const -> 클래스내 변수 변경 금지
    const E& front() const;
    void addFront(const E& e);
    void removeFront();
    int size() const;
    void print() const;
private:
    SNode<E>*head;
    int length;
};

template <typename E>
SLinkedList<E>::SLinkedList(): head(nullptr), length(0) {} // 생성자
template <typename E>
SLinkedList<E>::~SLinkedList(){while(!empty()) removeFront();} // 소멸자
template <typename E>
bool SLinkedList<E>::empty() const { return head == nullptr; } // 비었는지?
template <typename E>
const E& SLinkedList<E>::front() const { return head->elem; } // 맨앞원소
template <typename E>
void SLinkedList<E>::addFront(const E& e){ // 맨앞에 노드 더하기
    SNode<E> *v = new SNode<E>;  // 새로운 노드 생성
    v->elem = e; // 이 노드의 값설정
    v->next = head; // 이 노드의 다음을 현재 헤드로 지정
    head = v; // 이 노드를 헤드로 지정
    length++;
}
template<typename E>
void SLinkedList<E>::removeFront(){ // 맨앞에 노드 제거하기
    SNode<E>* old = head; // 현재 헤드를 임시노드에 저장
    head = old->next; // 헤드를 다음노드로 지정
    delete old; // 임시노드 삭제
    length--;
}
template <typename E>
int SLinkedList<E>::size() const{ return length;}

template <typename E>
void SLinkedList<E>::print() const{
    SNode<E> *curr = head;
    while(curr->next != nullptr){
        cout << curr->elem << ' ';
        curr = curr->next;
    }
    cout << '\n';
}


int main(){
    SLinkedList<int> a;
    for(int i =0; i < 10; i++){
        a.addFront(i);
    }
    a.print();
}