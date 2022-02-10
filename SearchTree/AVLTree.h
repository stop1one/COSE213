#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include "SearchTree.h"

template <typename E>  class AVLTree;


template <typename E>
  class AVLEntry : public E {				// an AVL entry
  private:
    int ht;						// node height
  protected:						// local types
    typedef typename E::Key K;				// key type
    typedef typename E::Value V;			// value type
    int height() const { return ht; }			// get height
    void setHeight(int h) { ht = h; }			// set height
  public:						// public functions
    AVLEntry(const K& k = K(), const V& v = V())	// constructor
        : E(k,v), ht(0) { }	
    friend class AVLTree<E>;				// allow AVLTree access
  };

//
// AVL Tree class
//  
template <typename E>					// an AVL tree
  class AVLTree : public SearchTree< AVLEntry<E> > {
  public:						// public types
    typedef AVLEntry<E> Entry;			// an entry
    typedef typename SearchTree<Entry>::Iterator Iterator; // an iterator
  protected:						// local types
    typedef typename Entry::Key K;			// a key
    typedef typename Entry::Value V;			// a value
    typedef SearchTree<Entry> ST;			// a search tree
    typedef typename ST::TPos TPos;			// a tree position
  public:						// public functions
    AVLTree();						// constructor
    Iterator insert(const K& k, const V& x);		// insert (k,x)
    void erase(const K& k);	// remove key k entry
    void erase(const Iterator& p);			// remove entry at p
  protected:						// utility functions 
    int height(const TPos& v) const;			// node height utility
    void setHeight(TPos v);				// set height utility
    bool isBalanced(const TPos& v) const;		// is v balanced?
    TPos tallGrandchild(const TPos& v) const;		// get tallest grandchild
    void rebalance(const TPos& v);			// rebalance utility
    TPos restructure(const TPos& v); 			// restructure
  };

      
#ifndef AVLTREE_TXX
#define AVLTREE_TXX
#include "AVLTree.txx"

#endif
#endif