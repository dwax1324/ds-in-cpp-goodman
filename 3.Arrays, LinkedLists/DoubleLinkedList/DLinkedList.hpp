
/*
    created at: 2021-02-02
*/

#include <ostream>


// 프로토타입
template <typename T> class DLinkedList;
template <typename T> std::ostream& operator << (std::ostream&, const DLinkedList<T>&);


template <typename T>
class DNode{
private:
    T elem;              // 노드 값
    DNode* prev;            // 이전 노드 포인터
    DNode* next;            // 다음 노드 포인터
    friend class DLinkedList<T>;// DLinkedList의 접근을 허용(friend)
};

template <typename T>
class DLinkedList{
public:
    friend std::ostream& operator<< <T>(std::ostream&, const DLinkedList<T>&);
    DLinkedList();                  //생성자
    ~DLinkedList();                 //소멸자
    bool empty() const;             // 비었는지?
    const T& front() const;      // 맨앞원소접근
    const T& back() const;       // 맨뒤원소접근
    void addFront(const T& e);   // 맨앞원소에 삽입
    void addBack(const T&e);     // 맨뒤원소에 삽입
    void removeFront();             // 맨앞원소 삭제
    void removeBack();              // 맨뒤원소 삭제
private:
    DNode<T>* header;                  // 리스트 보초병
    DNode<T>* trailer;
protected:                             // 지역 유틸
    void add(DNode<T>* v, const T& e); // v노드 이전에 삽입한다.
    void remove(DNode<T>* v);             // v노드를 삭제한다.
};

template <typename T>
DLinkedList<T>::DLinkedList(){             // 생성자
    header = new DNode<T>;                 // 보초병생성
    trailer = new DNode<T>;
    header->next = trailer;             // 서로를 마주보게함
    trailer->prev = header;
}

template <typename T>
DLinkedList<T>::~DLinkedList(){            // 소멸자
    while(!empty()) removeFront();      // 보초병 제외 모든 노드 삭제
    delete header;                      // 보초병 삭제
    delete trailer;
}

template <typename T>
bool DLinkedList<T>:: empty() const{       
    return (header->next == trailer);
}
template <typename T>
const T& DLinkedList<T>::back() const{
    return trailer->prev->elem;
}
template <typename T>
const T& DLinkedList<T>::front() const{
   return header->next->elem;
}

template <typename T>
void DLinkedList<T>::add(DNode<T>* v, const T& e){ // v이전에 끼워넣기
    DNode<T>* u = new DNode<T>;
    u->elem = e;          // e이전에 새로운 노드 u를 만들고 값을 준다
    u->next = v;                                // u의 next는 v를 가르킨다.
    u->prev = v->prev;                          // u의 prev는 v의 prev다.
    v->prev->next = u;
    v->prev = u;                // v의 이전노드와 v사이에 u를 끼워넣는다.
}


template <typename T>
void DLinkedList<T>::addFront(const T& e){
    add(header->next, e);
}

template <typename T>
void DLinkedList<T>::addBack(const T& e){
    add(trailer,e);
}


template <typename T>
void DLinkedList<T>::remove(DNode<T>* v){ // remove node v
    DNode<T>*u = v->prev;              // predecessor (앞노드)
    DNode<T>*w = v->next;              // successor (뒷노드)
    u->next = w;                    // v를 리스트로부터 unlink
    w->prev = u;
    delete v;
}


template <typename T>
void DLinkedList<T>::removeFront(){
    remove(header->next);
}


template <typename T>
void DLinkedList<T>::removeBack(){
    remove(trailer->prev);
}


template <typename T>
std::ostream& operator <<(std::ostream& out , const DLinkedList<T>& DL){
    DNode<T> *p = DL.header->next;
    out << "header" << " ↔ ";
    while(p!= DL.trailer){
        out << p->elem << " ↔ ";
        p = p->next;
    }
    out << "trailer";
    return out;
}