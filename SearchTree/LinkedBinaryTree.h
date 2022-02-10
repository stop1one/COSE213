#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <list>

using namespace std;

//
// Binary Tree Class
//
//typedef int Elem;					// base element type



template <typename K, typename V>
  class Entry {						// a (key, value) pair
  public:						// public functions
    typedef K Key;				// a key
    typedef V Value;
  
    Entry(const K& k = K(), const V& v = V())		// constructor
      : _key(k), _value(v) { }	
    const K& key() const { return _key; }		// get key
    const V& value() const { return _value; }		// get value
    void setKey(const K& k) { _key = k; }		// set key
    void setValue(const V& v) { _value = v; }		// set value
  private:						// private data
    K _key;						// key
    V _value;						// value
  };
  
  
typedef Entry<int,float> Elem;  

template <typename E>
class LinkedBinaryTree {
  protected:
	struct Node {					// a node of the tree
      E    elt;					// element value
      Node*   par;					// parent
      Node*   left;					// left child
      Node*   right;					// right child
      Node() : elt(), par(NULL), left(NULL), right(NULL) { } // constructor
    };
    
  public:
    class Position {					// position in the tree
    //private:
    public:
      Node* v;						// pointer to the node
    public:
      Position(Node* _v = NULL) : v(_v) { }		// constructor
      E& operator*() const					// get element
        { return v->elt; }
      Position left() const				// get left child
        { return Position(v->left); }
      Position right() const				// get right child
        { return Position(v->right); }
      Position parent() const				// get parent
        { return Position(v->par); }
      bool isRoot() const				// root of the tree?
        { return v->par == NULL; }
      bool isExternal() const				// an external node?
        { return v->left == NULL && v->right == NULL; }
    
    	// additional
      bool isInternal() const
      	{ return !isExternal(); }  
      bool operator==(const Position& p) const		// are iterators equal?
        { return v == p.v; }
      bool operator!=(const Position& p) const		// are iterators equal?
        { return v != p.v; }
    
    
    
      friend class LinkedBinaryTree;			// give tree access
    };
	typedef std::list<Position> PositionList;		// list of positions

  public:
    LinkedBinaryTree();					// constructor
    int size() const;					// number of nodes
    bool empty() const;					// is tree empty?
    Position root() const;				// get the root
    PositionList positions() const;  			// list of nodes
    void addRoot();					// add root to empty tree
    void expandExternal(const Position& p);		// expand external node
    Position removeAboveExternal(const Position& p);	// remove p and parent
    // housekeeping functions omitted...
  protected: 						// local utilities
    void preorder(Node* v, PositionList& pl) const;	// preorder utility
  private:
    Node* _root;					// pointer to the root
    int n;						// number of nodes
  };
  
  
  //
  // Implementation
  //
  
  template <typename E>
  void LinkedBinaryTree<E>::expandExternal(const Position& p) {
    Node* v = p.v;					// p's node
    v->left = new Node;					// add a new left child
    v->left->par = v;					// v is its parent
    v->right = new Node;				// and a new right child
    v->right->par = v;					// v is its parent
    n += 2;						// two more nodes
  }
  
  template <typename E>
  typename LinkedBinaryTree<E>::PositionList LinkedBinaryTree<E>::positions() const {
  PositionList pl;
  preorder(_root, pl);					// preorder traversal
  return PositionList(pl);				// return resulting list
}

// preorder traversal
template <typename E>
void LinkedBinaryTree<E>::preorder(Node* v, PositionList& pl) const {
  pl.push_back(Position(v));				// add this node
  if (v->left != NULL)					// traverse left subtree
    preorder(v->left, pl);
  if (v->right != NULL)					// traverse right subtree
    preorder(v->right, pl);
}

template <typename E>
typename LinkedBinaryTree<E>::Position				// remove p and parent
  LinkedBinaryTree<E>::removeAboveExternal(const Position& p) {
    Node* w = p.v;  Node* v = w->par;			// get p's node and parent
    Node* sib = (w == v->left ?  v->right : v->left);
    if (v == _root) {					// child of root?
      _root = sib;					// ...make sibling root
      sib->par = NULL;
    }
    else {
      Node* gpar = v->par;				// w's grandparent
      if (v == gpar->left) gpar->left = sib; 		// replace parent by sib
      else gpar->right = sib;
      sib->par = gpar;
    }
    delete w; delete v;					// delete removed nodes
    n -= 2;						// two fewer nodes
    return Position(sib);
  }
  
  template <typename E>
  LinkedBinaryTree<E>::LinkedBinaryTree()			// constructor
    : _root(NULL), n(0) { }
    
  template <typename E>  
  int LinkedBinaryTree<E>::size() const			// number of nodes
    { return n; }
    
  template <typename E>  
  bool LinkedBinaryTree<E>::empty() const			// is tree empty?
    { return size() == 0; }
    
  template <typename E>  
  typename LinkedBinaryTree<E>::Position LinkedBinaryTree<E>::root() const // get the root
    { return Position(_root); }
    
  template <typename E>  
  void LinkedBinaryTree<E>::addRoot()			// add root to empty tree
    { _root = new Node; n = 1; }
  
  #endif