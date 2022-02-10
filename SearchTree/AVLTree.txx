//
// Implementation
//
template <typename E>					// constructor
  AVLTree<E>::AVLTree() : ST() { }

template <typename E>					// node height utility
  int AVLTree<E>::height(const TPos& v) const
    { return (v.isExternal() ? 0 : (*v).height()); }

template <typename E>					// set height utility
  void AVLTree<E>::setHeight(TPos v) {
    int hl = height(v.left());
    int hr = height(v.right());
    (*v).setHeight(1 + std::max(hl, hr));			// max of left & right
  }

template <typename E>					// is v balanced?
  bool AVLTree<E>::isBalanced(const TPos& v) const {	
    int bal = height(v.left()) - height(v.right());
    return ((-1 <= bal) && (bal <= 1));
  }

template <typename E>					// get tallest grandchild
  typename AVLTree<E>::TPos AVLTree<E>::tallGrandchild(const TPos& z) const {
    TPos zl = z.left();
    TPos zr = z.right();
    if (height(zl) >= height(zr))			// left child taller
      if (height(zl.left()) >= height(zl.right()))
        return zl.left();
      else
        return zl.right();
    else 						// right child taller
      if (height(zr.right()) >= height(zr.left()))
        return zr.right();
      else
        return zr.left();
  }


template <typename E>					// remove key k entry
  void AVLTree<E>::erase(const K& k) {
    
    try {
        TPos temp = this->finder(k, ST::root());
        if (temp.isExternal())
            throw "Erase of nonexistent";
        TPos ers = this->eraser(temp);
        rebalance(ers);
    }
    catch (const char *err) {
        std::cout << err << std::endl;
    }
  }

template <typename E>					// insert (k,x)
  typename AVLTree<E>::Iterator AVLTree<E>::insert(const K& k, const V& x) {
    
    // ToDo
    TPos temp = ST::inserter(k, x);
    setHeight(temp);
    rebalance(temp);
    return Iterator(temp);
  }
  
template <typename E>					// rebalancing utility
  void AVLTree<E>::rebalance(const TPos& v) {
    
    // ToDo
    TPos temp = v;
    while (temp != ST::root()){
        temp = temp.parent();
        setHeight(temp);
        if(!isBalanced(temp)) {
            TPos tlst = tallGrandchild(temp);
            temp = restructure(tlst);
            setHeight(temp.left());
            setHeight(temp.right());
            setHeight(temp);
        }
    }
    
  }

template <typename E>				// Binary Search Tree Rotation
  typename AVLTree<E>::TPos AVLTree<E>::restructure(const TPos& v) {

	// ToDo
    TPos pv = v.parent();
    TPos gpv = pv.parent();
    TPos ggpv = gpv.parent();
    bool left = true;
    if (ggpv.right() == gpv) left = false; 

    // case 1 (single rotation)
    if (gpv.right() == pv && pv.right() == v){
        pv.v->left->par = gpv.v;        //change par
        pv.v->par = gpv.v->par;
        gpv.v->par = pv.v;
        gpv.v->right = pv.v->left;      //change child
        pv.v->left = gpv.v;
        if (left) ggpv.v->left = pv.v;
        else ggpv.v->right = pv.v;

        return pv;
    }
    // case 2 (single rotation)
    if (gpv.left() == pv && pv.left() == v){
        pv.v->right->par = gpv.v;        //change par
        pv.v->par = gpv.v->par;
        gpv.v->par = pv.v;
        
        gpv.v->left = pv.v->right;      //change child
        pv.v->right = gpv.v;
        if (left) ggpv.v->left = pv.v;
        else ggpv.v->right = pv.v;

        return pv;
    } 
    // case 3 (double rotation)
    if (gpv.right() == pv && pv.left() == v){
        v.v->left->par = gpv.v;         //change par
        v.v->right->par = pv.v;
        v.v->par = gpv.v->par;
        pv.v->par = v.v;
        gpv.v->par = v.v;
        
        gpv.v->right = v.v->left;       //change child
        pv.v->left = v.v->right;
        v.v->left = gpv.v;
        v.v->right = pv.v;
        if (left) ggpv.v->left = v.v;
        else ggpv.v->right = v.v;

        return v;
    }
    if (gpv.left() == pv && pv.right() == v){
        v.v->left->par = pv.v;         //change par
        v.v->right->par = gpv.v;
        v.v->par = gpv.v->par;
        pv.v->par = v.v;
        gpv.v->par = v.v;

        pv.v->right = v.v->left;        //change child
        gpv.v->left = v.v->right;
        v.v->left = pv.v;
        v.v->right = gpv.v;
        if (left) ggpv.v->left = v.v;
        else ggpv.v->right = v.v;

        return v;
    }
  }

