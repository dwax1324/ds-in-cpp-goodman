#include <bits/stdc++.h>
#include "BinaryTree.hpp"
template<typename K, typename V>

class Entry{
public:
    typedef K Key;
    typedef V Value;
public:
    Entry(const K& k = K(), const V& v = V()): _Key(k), _value(v){}
    const K& key() const{ return _Key;}
    const V& value() const{ return _value; }
    void setKey(const K& k) {_Key = k;}
    void setValue(const V& v) {_value=v;}
private:
    K _Key;
    V _value;
};

template<typename E>
class SearchTree{
public:
    typedef typename E::Key K;
    typedef typename E::value V;
    class Iterator;
public:
    SearchTree();
    int size() const;
    bool empty() const;
    Iterator find(const K& k);
    Iterator insert(const K& k, const V& x);
    void erase(const K& k);
    void erase(const Iterator& p);
    Iterator begin();
    Iterator end();
protected:
    typedef BinaryTree<E> BinaryTree;
    typedef typename BinaryTree::Position TPos;
    TPos root() const;
    TPos finder(const K& k, const TPos& v);
    TPos inserter(const K& k, const V& x);
    TPos eraser(TPos& v);
    TPos restructure(const TPos& v);
private:
    BinaryTree T;
    int n;
public:
// typedef typename E::Iterator TPos;
    class Iterator{
    private:
        TPos tp;
    public:
        Iterator(const TPos &tpp) : tp(tpp) {}
        const E& operator*() const { return *tp;}
        E& operator*() {return *tp;}
        bool operator== (const Iterator& p) const{
            return tp == p.tp;
        }
        Iterator& operator++();
        friend class SearchTree;
    };
};



template <typename E>
typename SearchTree<E>::Iterator& SearchTree<E>::Iterator::operator++() {
  TPos w = tp.right();
  if (w.isInternal()) {
	do { tp = w; w = w.left(); }
	while (w.isInternal());
  } else {
	w = tp.parent();
	while (tp == w.right()) { tp = w; w = w.parent(); }
	tp = w;
  }
  return *this;	
}

/**
 * @brief Binary Search Tree constructor
 *
 * The default constructor creates a super root using the
 * Binary tree, and uses it's left subtree as virtual
 * tree root.*/
template <typename E>
SearchTree<E>::SearchTree() : T(), n(0) {
  T.addRoot();
  T.expandExternal(T.root());
}

/**
 * @brief Root function utility
 */
template <typename E>
typename SearchTree<E>::TPos SearchTree<E>::root() const {
  return T.root().left();
}

/** 
 * @brief begin function 
 * @returns Iterator
 */
template <typename E>
typename SearchTree<E>::Iterator SearchTree<E>::begin() {
  TPos v = root();				// Start at virtual root
  while (v.isInternal()) v = v.left(); // Find leftmost node
  return Iterator(v.parent());
}

/** 
 * @brief end function 
 * @returns Iterator
 */
template <typename E>
typename SearchTree<E>::Iterator SearchTree<E>::end() { return Iterator(T.root()); }


/**
 * @brief Finder for the key searching
 * @returns SearchTree<E>::TPos
 */
template <typename E>
typename SearchTree<E>::TPos SearchTree<E>::finder(const K& k, const TPos& v) {
  if (v.isExternal()) return v;	// key not found
  if(k < v.key()) return finder(k, v.left()); // search the left subtree
  else if (v.key() < k) return finder(k, v.right()); // search the right tree
  else return v;				// Found it buddy!
}

/**
 * @brief Finder for the key search
 * @returns Iterator
 */
template <typename E>
typename SearchTree<E>::Iterator SearchTree<E>::find(const K& k) {
  TPos v = finder(k, root());	// search from virtual root
  if (v.isInternal()) return Iterator(v); // found it
  else return end();					  // woops, there is nothing
}

/**
 * @brief Inserter utility for the insert method
 * @returns SearchTree<E>::TPos
 */
template <typename E>
typename SearchTree<E>::TPos SearchTree<E>::inserter (const K& k, const V& x) {
  TPos v = finder(k, root());	// search from virtual root
  while (v.isInternal())		// key already there?
	v = finder (k, v.right());
  T.expandExternal(v);			// add new internal node
  v.key(k); v.value(x);			// set entry
  n++;							// there are more entries now
  return v;						// return the position
}

/** @brief Insert method
 * returns Iterator
 */
template <typename E>
typename SearchTree<E>::Iterator SearchTree<E>::insert(const K& k, const V& x) {
  TPos v = inserter(k, x);
  return Iterator(v);
}

/**
 * @brief Eraser utility
 * @returns TPos
 */
template <typename E>
typename SearchTree<E>::TPos SearchTree<E>::eraser(TPos& v) {
  TPos w;
  if (v.left().isExternal()) w = v.left(); // remove from left
  else if (v.right().isExternal()) w = v.right(); // remove from right
  else {										  // both internal?
	w = v.right();								  // go to the right tree
	do { w = w.left(); } while (w.isInternal());  // get leftmost node
	TPos u = w.parent();
	v->setKey(u->key()); v->setValue(u->value()); // copy w's parent to v
  }
  n--;							// one less entry
  return T.removeAboveExternal(w); // remove w and parent
}

/**
 * @brief Erase by key method uses eraser utility
 */
template <typename E>
void SearchTree<E>::erase(const K& k) {
  TPos v = finder(k, root());	// search from virtual root
  if (v.isExternal())			// not found?
	throw std::invalid_argument("Erase of nonexistent");
  eraser(v);					// remove it
}

/**
 * @brief Erase by iterator method uses eraser utility
 */
template <typename E>
void SearchTree<E>::erase(const Iterator& p) { eraser(p.v); } // erase at p
