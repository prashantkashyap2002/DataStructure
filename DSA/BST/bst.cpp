#include "bst.h"
#if 1
int main ()
{
  BST<int> bst(10);
  bst.insert(5);
  bst.insert(2);
  bst.insert(15);
  bst.insert(12);
  bst.insert(7);
  bst.insert(18);
  bst.insert(7);
  bst.insert(17);
  bst.insert(16);
  bst.print();
  bst.remove(16);
  bst.print();
  bst.find(12);
  bst.find(9);
  cout << "Max:" << bst.findMax() << " min:" << bst.findMin();
  cout << " MaxDepth of BST:" << bst.findDepth();
  cout << " BFS: "; 
  bst.bfs();
  cout << " DFS: "; 
  bst.dfs();
}
#endif 