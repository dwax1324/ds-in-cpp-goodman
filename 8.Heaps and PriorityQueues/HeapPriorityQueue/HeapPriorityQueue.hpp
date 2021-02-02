
#include <vector>
using namespace std;

template <typename E>
class VectorCompleteTree {
private:
  std::vector<E> V;		// Tree constents
public:
  typedef typename std::vector<E>::iterator Position; // Position in the tree
protected:
  Position pos(int i) {		// map index to a position
    return V.begin() + i;
  }
  int idx(const Position& p) const { // map a position to index
    return p - V.begin();
  }
public:
  VectorCompleteTree() : V(1) {} // constructor
  int size() const { return V.size() - 1; } // Size of the tree
  Position left (const Position& p) { return pos(2*idx(p)); } // left position
  Position right (const Position& p) { return pos(2*idx(p)) + 1; } // right position
  Position parent (const Position& p) { return pos(idx(p) >> 1); } // parent position
  bool hasLeft ( const Position& p) const { return 2*idx(p) <= size(); } // Is there left?
  bool hasRight ( const Position& p) const { return 2*idx(p) + 1 <= size(); } // Is there right?
  bool isRoot ( const Position& p) const { return idx(p) == 1; } // Is root?
  Position root() { return pos(1); }				 // Get the root
  Position last() { return pos(size()); }			 // Get the last element
  void addLast(const E& e) { V.push_back(e); }			 // Add element to the end
  void removeLast() { V.pop_back(); }				 // Remove last element
  void swap(const Position& p, const Position& q) {		 // Swap two elementscV
    E e = *q;
    *q = *p;
    *p = e;
  }
};


template <typename E ,typename C>
class HeapPriorityQueue{
public:
    int size() const;
    bool empty() const;
    void insert(const E& e);
    const E& min();
    void removeMin();
private:
    VectorCompleteTree<E>T;
    C Less;
    typedef typename VectorCompleteTree<E>::Position Position;
};

template <typename E>
class Less {
public:
    bool operator()(const E&p, const E& q){
        return p < q;
    }
};

template <typename E ,typename C>
int HeapPriorityQueue<E,C>::size() const{
    return T.size();
}
template <typename E ,typename C>
bool HeapPriorityQueue<E,C>::empty() const{
    return size()==0;
}
template <typename E ,typename C>
const E& HeapPriorityQueue<E,C>::min(){
    return *(T.root());
}

template <typename E ,typename C>
void HeapPriorityQueue<E,C>::insert(const E& e){
    T.addLast(e);
    Position v = T.last();
    while(!T.isRoot(v)){
        Position u = T.parent(v);
        if(!Less(*v,*u)) break;
        T.swap(v,u);
        v= u;
    }
}
template <typename E ,typename C>
void HeapPriorityQueue<E,C>::removeMin(){
    if(size() == 1) T.removeLast();
    else{
        Position u = T.root();
        T.swap(u, T.last());
        T.removeLast();
        while(T.hasLeft(u)){
            Position v = T.left(u);
            if(T.hasRight(u) && Less(*(T.right(u)),*v)) v = T.right(u);
            if(Less(*v,*u)){
                T.swap(u,v);
                u = v;
            }
            else break;
        }

    }

}