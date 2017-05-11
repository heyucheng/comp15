
#ifndef BST_H
#define BST_H

#include <iostream>

using namespace std;

class BSTNode {
 public:

  /// Constructors
  explicit BSTNode(int aKey) 
    : mKey(aKey), mLeft(NULL), mRight(NULL), mParent(NULL)
  {}

  explicit BSTNode(int aKey, BSTNode* aLeft, BSTNode* aRight, BSTNode* aParent)
    : mKey(aKey), mLeft(aLeft), mRight(aRight), mParent(aParent)
  {}

  /// Getting and setting key
  int key() const { return mKey; }
  void setKey(int aData) { mKey = aData; }

  /// Getting and setting left child node
  BSTNode* left() { return mLeft; }
  const BSTNode* left() const { return mLeft; }
  void setLeft(BSTNode* aLeft) { mLeft = aLeft; }

  /// Getting and setting right child node
  BSTNode* right() { return mRight; }
  const BSTNode* right() const { return mRight; }
  void setRight(BSTNode* aRight) { mRight = aRight; }

  /// Getting and setting the parent node
  BSTNode* parent() { return mParent; }
  const BSTNode* parent() const { return mParent; }
  void setParent(BSTNode* aParent) { mParent = aParent; }

  /// Getting preds and succs
  BSTNode* pred() const;
  BSTNode* succ() const;

  /// Some utilities
  void swapLeft(); 
  void swapRight();
  void detachFromParent();
  void inorder() const;
  void preorder() const;
  void postorder() const;

  /// Find a node in the BST containing the given key
  BSTNode* find(int aKey);
  /// Find min
  int getMin() const;
  /// Find max
  int getMax() const;
  /// Output
  void output(ostream& s) const;

 private:
  /// Key
  int mKey;
  /// Left child
  BSTNode* mLeft;
  /// Right child
  BSTNode* mRight;
  /// Parent
  BSTNode* mParent;
};

class BST {
 public:  
  BST() 
    : mRoot(NULL)
    {}
  
  /// Setting and getting root
  void setRoot(BSTNode* aNode) { mRoot = aNode; }
  BSTNode* root() { return mRoot; }
  const BSTNode* root() const { return mRoot; }

  /// Find a node in the BST containing the given key
  BSTNode* find(int aKey)
  { 
    if (mRoot) 
      return mRoot->find(aKey); 
    else
      return NULL;
  }

  /// Insert a new key in the BST
  void insert(int aKey);
  
  /// Find min
  int getMin() const
  { 
    if (mRoot == NULL) {
      cout << "No node in the tree." << endl;
      exit(1);
    } 
    return mRoot->getMin(); 
  }

  /// Find max
  int getMax() const
  { 
    if (mRoot == NULL) {
      cout << "No node in the tree." << endl;
      exit(1);
    } 
    return mRoot->getMax(); 
  }

  /// delete a key in the BST
  void remove(int aKey);

  /// Print inorder
  void inorder() const;

  /// Print preorder
  void preorder() const;

  /// Print postorder
  void postorder() const;

  /// Trivially remove a node n
  void trivialRemove(BSTNode* n);

  /// Output the tree
  void output(ostream& s) const;

  /// Search for an inorder index containing the given item in the given range
  int searchIndex(int* inorder, int start, int end, int rootItem);

  /// Construct the tree from traversals
  BSTNode* constructTreeFromTraversals(int* preorder, 
				       int* inorder, 
				       int start, 
				       int end, 
				       int& currIndex);
    
 private:
  /// Root pointer
  BSTNode* mRoot;
};

ostream& operator<<(ostream& s, const BST& bst);

#endif
