#ifndef SEARCHTREE_H
#define SEARCHTREE_H

#include <iostream>
#include "LinkedBinaryTree.h"

//
// SearchTree Class
//  
template <typename E>
class SearchTree {					// a binary search tree
  public: 						// public types
    typedef typename E::Key K;				// a key
    typedef typename E::Value V;			// a value
    class Iterator;					// an iterator/position
  public:						// public functions
    SearchTree();					// constructor
    int size() const; 					// number of entries
    bool empty() const;					// is the tree empty?
    Iterator find(const K& k);				// find entry with key k
    Iterator insert(const K& k, const V& x);		// insert (k,x)
    //Iterator rooot();
    void erase(const K& k);				// remove key k entry
    void erase(const Iterator& p);			// remove entry at p
    Iterator begin();					// iterator to first entry
    Iterator end();					// iterator to end entry
  protected:						// local utilities
    typedef LinkedBinaryTree<E> BinaryTree;		// linked binary tree
    typedef typename BinaryTree::Position TPos;		// position in the tree
    TPos root() const;					// get virtual root
    TPos finder(const K& k, const TPos& v);		// find utility
    TPos inserter(const K& k, const V& x);		// insert utility
    TPos eraser(TPos& v);				// erase utility
    TPos restructure(const TPos& v); 			// restructure
    
  private: 						// member data
    BinaryTree T;					// the binary tree
    int n;						// number of entries
  public:
    class Iterator {	                      		// an iterator/position
    private:
      TPos v;						// which entry
    public:
      Iterator(const TPos& vv) : v(vv) { }		// constructor
      const E& operator*() const { return *v; }		// get entry (read only)
      E& operator*() { return *v; }			// get entry (read/write)
      bool operator==(const Iterator& p) const		// are iterators equal?
        { return v == p.v; }   
      bool operator!=(const Iterator& p) const		// are iterators not equal?
        { return v != p.v; }
      Iterator& operator++();				// inorder successor
      friend class SearchTree;				// give search tree access
    };
  };
  
      
#ifndef SEARCHTREE_TXX
#define SEARCHTREE_TXX
#include "SearchTree.txx"
#endif
#endif