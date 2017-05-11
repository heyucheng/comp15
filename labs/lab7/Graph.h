
#ifndef GRAPH_H
#define GRAPH_H

#include "sll.h"

class Node {
 public:
Node(int aId) : mId(aId), mAdjNodes(), mColor(Node::WHITE)
  {}
  int id() const { return mId; }
  void addEdgeTo(Node* aNode) { mAdjNodes.addFront(aNode); }
  int numAdjNodes() const { return mAdjNodes.size(); }
  void outputEdges(std::ostream& s) const
  {
    if (numAdjNodes() == 0) {
      return;
    }
    for (const SLLNode* curr = mAdjNodes.head();
	 curr != NULL; curr = curr->next()) {
      Node* dstNode = curr->value();
      s << id() << " -> " << dstNode->id() << std::endl;
    }
  }

  SLinkedList& getAdjNodes()
  {
	  return mAdjNodes;
  }

   enum ColorType 
 {
   WHITE,
   GRAY,
   BLACK
 };

  ColorType color()
  {
	  return mColor;
	}

  void setColor(ColorType aColor)
  {
	  mColor = aColor;
  }
 
 private:
  int mId;
  SLinkedList mAdjNodes;
  ColorType mColor;
};

class Graph {
 public:
  int numNodes() const { return mNodes.size(); }
  void addNode(int aId)
  {
    Node* aNode = new Node(aId);
    mNodes.addFront(aNode);
  }
  
  Node* find(int aId) const
  {
    for (const SLLNode* curr = mNodes.head();
	 curr != NULL; curr = curr->next()) {
      if (curr->value()->id() == aId) {
	return curr->value();
      }
    }
    return NULL;
  }

  void addEdge(int aNodeId1, int aNodeId2)
  {
    Node* n1 = find(aNodeId1);
    Node* n2 = find(aNodeId2);
    if (n1 != NULL && n2 != NULL) {
      n1->addEdgeTo(n2);
    }
  }

  bool isCyclic() const;
  bool isCyclicHelp(Node* aNode) const;
  void output(std::ostream& s) const;

 private:
  SLinkedList mNodes;
};

std::ostream& operator<<(std::ostream& s, const Graph& g);

#endif
