#ifndef SLL_H
#define SLL_H

#include <iostream>
#include <cassert>

class Node;

using namespace std;

class SLLNode {
  public:
    /// Constructors
    SLLNode(Node* aValue) 
      : mValue(aValue),mNext(NULL)
    {
    }
      
    SLLNode(Node* aValue, SLLNode *aNext)
      : mValue(aValue), mNext(aNext)
    {
    }
    
    /// Get value
    Node* value() const
    {
      return mValue;
    }

    /// Get next node for const node receiver
    const SLLNode *next() const
    {
      return mNext;
    }
    
    /// Get next node for non-const node receiver
    SLLNode *next()
    {
      return mNext;
    }

    /// Set next node
    void setNext(SLLNode* aNext)
    {
      mNext = aNext;
    }
    
    /// Insert a new node with aValue after this node
    void insertAfter(Node* aValue)
    {
      mNext = new SLLNode(aValue, mNext);
    }      

    /// Delete after this node
    void deleteAfter()
    {
	if (mNext == NULL) {
	  return;
	}
	SLLNode *node = mNext;
	mNext = node->next();
	delete node;
    }
    
  private:
    Node* mValue;
    SLLNode* mNext;
};
  

/// Singly Linked List with a head pointer, a tail pointer and size
class SLinkedList {
 public:
  /// Constructor
  SLinkedList()
    : mHead(NULL), mTail(NULL), mSize(0)
  {
  }

  /// Insert a node in the front of the list
  void addFront(Node* aValue)
  {
    mHead = new SLLNode(aValue, mHead);
    if (mTail == NULL) {
      // First entry
      mTail = mHead;
    }
    mSize++;
  }

  /// Insert a node in the back of the list
  void addBack(Node* aValue)
  {
    SLLNode* node = new SLLNode(aValue);
    if (mHead == NULL) {
      mHead = mTail = node;
    } else {
      mTail->setNext(node);
      mTail = node;
    }
    mSize++;
  }
    
  /// Delete the node from the front
  void removeFront()
  {
    assert((mHead == NULL && mTail == NULL) ||
	   mSize > 0);
    if (mHead == NULL) {
      return;
    }
    SLLNode *oldHead = mHead;
    mHead = mHead->next();
    if (mHead == NULL) {
      mTail = mHead;
    }
    delete oldHead;
    mSize--;
  }

  /// Delete everything
  void removeAll()
  {
    while(mSize > 0) {
      removeFront();
    }
    mHead = mTail = NULL;
    mSize = 0;
  }
  
  /// Get the value from the front
  Node* front() const
  {
    if (isEmpty()) {
      cout << "list empty." << endl;
      return NULL;
    }
    return mHead->value();
  }
  
  /// Get the value from the back
  Node* back() const
  {
    if (isEmpty()) {
      cout << "list empty." << endl;
      return NULL;
    }
    return mTail->value();
  }
    
  /// Check whether the list is empty
  bool isEmpty() const
  {
    return (size() == 0);
  }
  
  /// Get the size of the list
  int size() const
  {
    return mSize;
  }
  
  /// Copy constructor
  SLinkedList(const SLinkedList& other)
    : mHead(NULL), mTail(NULL), mSize(0)
  {
    if (!other.isEmpty()) {
      // Copy from other
      for (const SLLNode* curr = other.head(); curr != NULL; curr = curr->next()) {
	addBack(curr->value());
      }
    }
  }

  /// Assignment operator
  SLinkedList& operator=(const SLinkedList& other)
  {
    if (this == &other) {
      // self-assignment -- return otherwise bad things will happen
      return *this;
    }

    // Cleanup this list
    removeAll();

    // Copy from other
    if (!other.isEmpty()) {
      for (const SLLNode* curr = other.head(); curr != NULL; curr = curr->next()) {
	addBack(curr->value());
      }
    }
    return *this;
  }

  /// Destructor
  ~SLinkedList()
  {
    removeAll();
  }

  /// Get the head pointer
  SLLNode* head()
  {
    return mHead;
  }
  
  /// Get the head pointer
  const SLLNode* head() const
  {
    return mHead;
  }
  
 private:
  
  SLLNode* mHead;
  SLLNode* mTail;
  int mSize;
    
};

#endif
