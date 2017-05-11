
#include "Graph.h"

using namespace std;

int main()
{
  Graph g;
  int numNodes = 6;
 
  for (int i = 0; i < numNodes; ++i) {
    g.addNode(i);
  }
  
  g.addEdge(0, 1);
  g.addEdge(0, 2);
  g.addEdge(0, 4);
  g.addEdge(1, 5); // Comment and try again
  g.addEdge(2, 3);
  g.addEdge(3, 1);
  g.addEdge(5, 0);

  cout << g;

  if (g.isCyclic()) {
    cout << "Cycle detected." << endl;
  } else {
    cout << "No cycle detected." << endl;
  }
  return 0;
}
