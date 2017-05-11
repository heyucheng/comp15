// SplaySort.h

#ifndef SPLAY_SORT_H
#define SPLAY_SORT_H

#include "Array.h"
#include "bst.h"
#include "SortingAlgorithm.h"

class SplaySort : public SortingAlgorithm {
 public:
  virtual void sort(Array& A)
  {
    // Your Splay tree sort implementation goes here
    BST bst;
    for (int i = 0; i < A.length(); i++) {
      BSTNode* temp = bst.insert(A[i]);
    	splay(temp);
      bst.setRoot(temp);
    }
    int startIndex = 0;
    inorder(bst.root(), A, startIndex);
  }
 
  void inorder(BSTNode* root, Array& A, int i) {
  	if (root != NULL) {
  		if (root->left() != NULL) {
  			inorder(root->left(), A, i);
  		}
  		A[i] = root->key();
  		i++;
  		if (root->right() != NULL) {
  			inorder(root->right(), A, i);
  		}
  	}
  }

 
    /// Left Rotate
  void leftRotate(BSTNode* aNode)
  {
    BSTNode* temp = aNode->right();
    if (temp != NULL) {
      aNode->setRight(temp->left());
      if (temp->left() != NULL) {
        temp->left()->setParent(aNode);
      }
      temp->setParent(aNode->parent());
    }

    if (aNode->parent() != NULL) {
      if (aNode == aNode->parent()->left()) {
        aNode->parent()->setLeft(temp);
      } else if (aNode == aNode->parent()->right()) {
        aNode->parent()->setRight(temp);
      } 
    }

    if (temp != NULL) {
      temp->setLeft(aNode);
    }
    aNode->setParent(temp);
  }

  /// Right Rotate
  void rightRotate(BSTNode* aNode)
  {
    BSTNode* temp = aNode->left();
    if (temp != NULL) {
      aNode->setLeft(temp->right());
      if (temp->right() != NULL) {
        temp->right()->setParent(aNode);
      }
      temp->setParent(aNode->parent());
    }

    if (aNode->parent() != NULL) {
      if (aNode == aNode->parent()->left()) {
        aNode->parent()->setLeft(temp);
      } else if (aNode == aNode->parent()->right()) {
        aNode->parent()->setRight(temp);
      } 
    }

    if (temp != NULL) {
      temp->setRight(aNode);
    }
    aNode->setParent(temp);
  }
  

  void splay(BSTNode* aNode)
  {
    while (aNode->parent() != NULL) {
      if (aNode->parent()->parent() == NULL) {
        // zig;
        if (aNode->parent()->left() == aNode) {
          rightRotate(aNode->parent());
        } else {
          leftRotate(aNode->parent());
        }
      } else if (aNode->parent()->left() == aNode and aNode->parent()->parent()->left() == aNode->parent()) {
        // left of left zigzig
        rightRotate(aNode->parent()->parent());
        rightRotate(aNode->parent());
      } else if (aNode->parent()->right() == aNode and aNode->parent()->parent()->right() == aNode->parent()) {
        // right of right zigzig
        leftRotate(aNode->parent()->parent());
        leftRotate(aNode->parent());
      } else if (aNode->parent()->right() == aNode and aNode->parent()->parent()->left() == aNode->parent()) {
        // right of left zigzag
        leftRotate(aNode->parent());
        rightRotate(aNode->parent());
      } else if (aNode->parent()->left() == aNode and aNode->parent()->parent()->right() == aNode->parent()) {
        //left od right zigzag
        rightRotate(aNode->parent());
        leftRotate(aNode->parent());
      }
    }
  }
	

};

#endif

