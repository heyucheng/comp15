
#include <iostream>
#include "bst.h"

using namespace std;

/// Get predecessor
BSTNode* BSTNode::pred() const
{
  BSTNode* lc = const_cast<BSTNode*>(left());
  if (lc == NULL) {
    return NULL;
  }
  while (lc->right() != NULL) {
    lc = lc->right();
  }
  return lc;
}

/// Get successor
BSTNode* BSTNode::succ() const
{
  BSTNode* rc = const_cast<BSTNode*>(right());
  if (rc == NULL) {
    return NULL;
  }
  while (rc->left() != NULL) {
    rc = rc->left();
  }
  return rc;
}


/// Find min
int BSTNode::getMin() const
{
  if (left() == NULL) {
    return key();
  }
  return left()->getMin();
}

/// Find max
int BSTNode::getMax() const
{
  if (right() == NULL) {
    return key();
  }
  return right()->getMax();

}

/// Swap left
void BSTNode::swapLeft()
{
  BSTNode* c = left();
  BSTNode* p = parent();
  if (p->left() == this) {
    p->setLeft(c);
  } else {
    p->setRight(c);
  }
}

/// Swap right
void BSTNode::swapRight()
{
  BSTNode* c = right();
  BSTNode* p = parent();
  if (p->left() == this) {
    p->setLeft(c);
  } else {
    p->setRight(c);
  }
}


/// Detach from parent
void BSTNode::detachFromParent() 
{
  BSTNode* p = parent();
  if (p == NULL) {
    return;
  }
  if (p->left() == this) {
    p->setLeft(NULL);
  } else {
    p->setRight(NULL);
  }
}

void BSTNode::inorder() const
{
  if (left()) {
    left()->inorder();
  }
  cout << key() << endl;
  if (right()) {
    right()->inorder();
  }
}

void BSTNode::postorder() const
{
  if (left()) {
    left()->postorder();
  }
  if (right()) {
    right()->postorder();
  }
  cout << key() << endl;
}

void BSTNode::preorder() const
{
  cout << key() << endl;
  if (left()) {
    left()->preorder();
  }
  if (right()) {
    right()->preorder();
  }
}

/// Find a node in the BST containing the given key
BSTNode* BSTNode::find(int aKey) 
{
  if (key() == aKey) {
    // found
    return this;
  }
  if (aKey < key()) {
    if (left()) {
      return left()->find(aKey);
    } else {
      return this;
    }
  } else if (aKey > key()) {
    if (right()) {
      return right()->find(aKey);
    } else {
      return this;
    }
  }
  return NULL;
}

/// Print the tree starting from this node
void BSTNode::output(ostream& s) const
{
  static int count = 0;
  if (left() != NULL) {
    s << key() << " -> " << left()->key() << endl; // << " [label=\"L\"] " << endl;
    left()->output(s);
  } else {
    s << "NULL" << count << "[shape=point]" << endl;
    s << key() << " -> " << "NULL" << count++ << endl;
  }
  if (right() != NULL) {
    s << key() << " -> " << right()->key() << endl; // " [label=\"R\"] " << endl;
    right()->output(s);
  } else {
    s << "NULL" << count << "[shape=point]" << endl;
    s << key() << " -> " << "NULL" << count++ << endl;
  }
}

///////////////////////////////////////


/// Insert a new key in the BST
void BST::insert(int aKey)
{
  BSTNode* place = find(aKey);
  if (place == NULL) {
    // First node to be inserted
    mRoot = new BSTNode(aKey);
  } else if (aKey < place->key()) {
    // Node on the left of place
    place->setLeft(new BSTNode(aKey, NULL, NULL, place));
  } else {
    // Node on the right of place
    place->setRight(new BSTNode(aKey, NULL, NULL, place));
  }
}

// Cases 1, 2 and 3
void BST::trivialRemove(BSTNode* n)
{
  if (n->left() == NULL && 
      n->right() == NULL) {
    // Case 1: No children
    // Detach it from the parent
    n->detachFromParent();
    delete n;
    return;
  }
  if (n->left() == NULL &&
      n->right() != NULL) {
    // Case 2: n has only right child
    n->swapRight();
    delete n;
    return;
  }
  if (n->right() == NULL &&
      n->left() != NULL) {
    // Case 3: n has only left child
    n->swapLeft();
    delete n;
  }
}

/// delete a key in the BST
void BST::remove(int aKey)
{
  BSTNode* n = find(aKey);
  if (n == NULL ||
      n->key() != aKey) {
    // No node containing aKey
    return;
  }
  // Trivial remove
  trivialRemove(n);
  if (n->left() != NULL &&
      n->right() != NULL) {
    // Case 4: n has both left and right child
    BSTNode* s = n->succ();
    n->setKey(s->key());
    trivialRemove(s);
  } else {
    // Cases 1, 2 and 3
    trivialRemove(n);
  }
}

/// Print inorder
void BST::inorder() const
{
  if (mRoot) mRoot->inorder();
}

/// Print preorder
void BST::preorder() const
{
 if (mRoot) mRoot->preorder();
}

/// Print postorder
void BST::postorder() const
{
  if (mRoot) mRoot->postorder();
}

void BST::output(ostream& s) const
{
  s << "digraph{" << endl;
  if (mRoot) mRoot->output(s);
  s << "}" << endl;
}

int BST::searchIndex(int* inorder, int start, int end, int rootItem)
{
  for (int i = start; i <= end; ++i) {
    if (inorder[i] == rootItem) {
      return i;
    }
  }
  return -1;
}

BSTNode* BST::constructTreeFromTraversals(int* preorder, 
					  int* inorder,
					  int start,
					  int end,
					  int& currIndex)
{
  // Your implementation goes here
	if (start > end) {
		return NULL;
	}
	BSTNode* newNode = new BSTNode(preorder[currIndex]);
	if (currIndex == 0) {
		mRoot = newNode;
	}
  int index = searchIndex(inorder, start, end, preorder[currIndex]);
  
	currIndex++;
	if (start == end) {
		return newNode;
	}
	
	newNode->setLeft (constructTreeFromTraversals(preorder, inorder, start, index-1, currIndex));
	newNode->setRight (constructTreeFromTraversals(preorder, inorder, index+1, end, currIndex ));
  if (newNode->left() != NULL) {
    newNode->left()->setParent(newNode);  
  }
  if (newNode->right() != NULL) {
    newNode->right()->setParent(newNode);
  }
	return newNode;	
		
}

std::ostream& operator<<(std::ostream& s, const BST& bst)
{
  bst.output(s);
  return s;
}
