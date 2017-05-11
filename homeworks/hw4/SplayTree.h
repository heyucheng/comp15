
#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include <iostream>
#include "Array.h"
#include "bst.h"
#include <cassert>

using namespace std;

template<typename KeyT, typename ValueT>
class SplayTree : public BST<KeyT,ValueT> {
  public:  
    
    /// Find a node in the BST containing the given key
    BSTNode<KeyT,ValueT>* find(KeyT aKey)
    {
        BSTNode<KeyT,ValueT>* node = BST<KeyT,ValueT>::find(aKey);
        if (node != nullptr) {
            // Splay the node that is found or the node where the search ended
            splay(node);
        }
        return node;
    }

    /// Find a node in the BST containing the given key.
    /// If exact match not found, return nullptr but also set the approxMatchNode
    BSTNode<KeyT,ValueT>* findApprox(KeyT aKey, 
                                     BSTNode<KeyT,ValueT>*& approxMatchNode_lb,
                                     BSTNode<KeyT,ValueT>*& approxMatchNode_ub)
    {
        BSTNode<KeyT,ValueT>* node = BST<KeyT,ValueT>::findApprox(aKey, 
                                                                  approxMatchNode_lb,
                                                                  approxMatchNode_ub);
        if (node != nullptr) {
            // Splay the node that is found or the node where the search ended
            splay(node);
        } else {
	  if (approxMatchNode_lb)
            splay(approxMatchNode_lb);
	  if (approxMatchNode_ub)
	    splay(approxMatchNode_ub);
        }
        return node;
    }
  
    /// Find min
    BSTNode<KeyT,ValueT>* getMin() 
    { 
        BSTNode<KeyT,ValueT>* minBSTNode = BST<KeyT,ValueT>::getMin(); 
        if (minBSTNode != nullptr) {
            // Splay the min node
            splay(minBSTNode);
        }
        return minBSTNode;
    }

    /// Find max
    BSTNode<KeyT,ValueT>* getMax() 
    { 
        BSTNode<KeyT,ValueT>* maxBSTNode = BST<KeyT,ValueT>::getMax(); 
        if (maxBSTNode != nullptr) {
            // Splay the max node
            splay(maxBSTNode);
        }
        return maxBSTNode;
    }

    /// Remvoe
    void remove(KeyT aKey) 
    { 
        BSTNode<KeyT,ValueT>* parentNode = BST<KeyT,ValueT>::remove(aKey); 
	if (parentNode != nullptr) {
            // Splay the parent node of the removed node
            splay(parentNode);
        }
    }




  public:

    /// Splay operation
    void splay(BSTNode<KeyT,ValueT>* aNode)
    {
        BSTNode<KeyT, ValueT>* parent = aNode->parent();
        if (parent == NULL) {
            return;
        }
        BSTNode<KeyT, ValueT>* grandParent = parent->parent();
        while (parent != NULL and grandParent != NULL) {
            if (grandParent->right() == parent and parent->left() == aNode) {
                zigLRzagRL(aNode, parent, grandParent);
            }
            else if (grandParent->right() == parent and parent->right() == aNode) {
                zigRLzigRL(aNode, parent, grandParent);
            }
            else if (grandParent->left() == parent and parent->right() == aNode) {
                zigRLzagLR(aNode, parent, grandParent);
            }
            else if (grandParent->left() == parent and parent->left() == aNode) {
                zigLRzigLR(aNode, parent, grandParent);
            }
            parent = aNode->parent();
            if (parent == NULL) {
                break;
            }
            grandParent = parent->parent();
            if (grandParent == NULL) {
                break;
            }
        }
        if (grandParent == NULL) {
            if (parent->left() == aNode) {
                zigLR(aNode, parent);
            } else {
                zigRL(aNode, parent);
            }
        }
      
    }
    
    ///zig left to right zag right to left; aNode is a left child of a right child
    void zigLRzagRL(BSTNode<KeyT, ValueT>* aNode, BSTNode<KeyT, ValueT>* aParent, BSTNode<KeyT, ValueT>* aGrandParent)
    {
        BSTNode<KeyT, ValueT>* ggParent = aGrandParent->parent();
        zigLR(aNode, aParent);
        zigRL(aNode, aGrandParent);
        if (ggParent != NULL){
            if (ggParent->left() == aGrandParent) {
                ggParent->setLeft(aNode);
                aNode->setParent(ggParent);
            } else {
                ggParent->setRight(aNode);
                aNode->setParent(ggParent);
            }
        }
    }

    ///zig right to left zag left to right; aNode is a right child of a left child
    void zigRLzagLR(BSTNode<KeyT, ValueT>* aNode, BSTNode<KeyT, ValueT>* aParent, BSTNode<KeyT, ValueT>* aGrandParent)
    {
        BSTNode<KeyT, ValueT>* ggParent = aGrandParent->parent();
        zigRL(aNode, aParent);
        zigLR(aNode, aGrandParent);
        if (ggParent != NULL){
            if (ggParent->left() == aGrandParent) {
                ggParent->setLeft(aNode);
                aNode->setParent(ggParent);
            } else {
                ggParent->setRight(aNode);
                aNode->setParent(ggParent);
            }
        }

    }

    ///zig left to right zig left to right; aNode is a left child of a left child
    void zigLRzigLR(BSTNode<KeyT, ValueT>* aNode, BSTNode<KeyT, ValueT>* aParent, BSTNode<KeyT, ValueT>* aGrandParent)
    {
        BSTNode<KeyT, ValueT>* ggParent = aGrandParent->parent();
        zigLR(aParent, aGrandParent);
        zigLR(aNode, aParent);
        if (ggParent != NULL){
            if (ggParent->left() == aGrandParent) {
                ggParent->setLeft(aNode);
                aNode->setParent(ggParent);
            } else {
                ggParent->setRight(aNode);
                aNode->setParent(ggParent);
            }
        }

    }

    ///zig right to left zig right to left; aNode is a right child of a right child
    void zigRLzigRL(BSTNode<KeyT, ValueT>* aNode, BSTNode<KeyT, ValueT>* aParent, BSTNode<KeyT, ValueT>* aGrandParent)
    {
        BSTNode<KeyT, ValueT>* ggParent = aGrandParent->parent();
        zigRL(aParent, aGrandParent);
        zigRL(aNode, aParent);
        if (ggParent != NULL){
            if (ggParent->left() == aGrandParent) {
                ggParent->setLeft(aNode);
                aNode->setParent(ggParent);
            } else {
                ggParent->setRight(aNode);
                aNode->setParent(ggParent);
            }
        }

    }

    /// zig; left to right, aNode is left child of root
    void zigLR(BSTNode<KeyT, ValueT>* aNode, BSTNode<KeyT, ValueT>* aParent)
    {
    
        BSTNode<KeyT, ValueT>* rightChild = aNode->right();
        aNode->setRight(aParent);
        aParent->setParent(aNode);
        aParent->setLeft(rightChild);
        if (rightChild != NULL) {
            rightChild->setParent(aParent);
        }
        if (BST<KeyT, ValueT>::root() == aParent) {
            BST<KeyT, ValueT>::setRoot(aNode);
            aNode->setParent(NULL);
        }
    }

    /// zig; right to left, aNode is right child of root
    void zigRL(BSTNode<KeyT, ValueT>* aNode, BSTNode<KeyT, ValueT>* aParent)
    {
        BSTNode<KeyT, ValueT>* leftChild = aNode->left();
        aNode->setLeft(aParent);
        aParent->setParent(aNode);
        aParent->setRight(leftChild);
        if (leftChild != NULL) {
            leftChild->setParent(aParent);
        }
        if (BST<KeyT, ValueT>::root() == aParent){
            BST<KeyT, ValueT>::setRoot(aNode);
            aNode->setParent(NULL);
        }
    }
    

    
};


#endif
