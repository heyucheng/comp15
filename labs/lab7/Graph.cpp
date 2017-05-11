
#include "Graph.h"
#include <iostream>
#include <fstream>

void Graph::output(std::ostream& s) const
{
  // Your code goes here
	cout << "digraph{" << endl;
	for (const SLLNode* node = mNodes.head(); node !=NULL; node = node->next()) {
		if (node->value()->getAdjNodes().head() == NULL) {
			s << node->value()->id() << endl;
		} 
		for (const SLLNode* adjNode = node->value()->getAdjNodes().head(); adjNode != NULL; adjNode = adjNode->next()){
			s << node->value()->id() << " -> " << adjNode->value()->id() << endl;
		}
	}
	cout << "}" << endl;
}

bool Graph::isCyclic() const
{
  // Your code goes here
	for (const SLLNode* node = mNodes.head(); node != NULL; node = node->next()) {
		node->value()->setColor(Node::WHITE);
	}
	for (const SLLNode* node = mNodes.head(); node != nullptr; node = node->next()) {
		if (isCyclicHelp(node->value()) == true) {
			return true;
		}
	}
	return false;

}

bool Graph::isCyclicHelp(Node* aNode) const
{
	if (aNode->color() == Node::WHITE) {
		aNode->setColor(Node::GRAY);
	}
	for (SLLNode* adjNode = aNode->getAdjNodes().head(); adjNode != NULL; adjNode = adjNode->next()) {
		if (adjNode->value()->color() == Node::WHITE and isCyclicHelp(adjNode->value()) == true) {
			return true;
		}
		if (adjNode->value()->color() == Node::GRAY) {
			return true;
		}
	}
	aNode->setColor(Node::BLACK);
	return false;

}
std::ostream& operator<<(std::ostream& s, const Graph& g)
{
  g.output(s);
}

