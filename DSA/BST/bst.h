#include <iostream>
#include <queue>

using namespace std;
template <typename T>
class bstNode {
  public:
    bstNode(T value) {
      this->data = value;
      this->left = nullptr;
      this->right = nullptr;
    }
    // Accessor API
    void setLeft (bstNode<T> *node) {
      this->left = node;
    }
    bstNode<T>* getLeft () {return this->left;}

    void setRight (bstNode<T> *node) {
      this->right = node;
    }
    bstNode<T>* getRight () {return this->right;}

    void setData (T value) {
      this->data = value;
    }
    T getData () {return data;}

  private:
    T data;
    bstNode<T> *left;
    bstNode<T> *right;
};

template <typename T>
class BST {
  public:
    BST () {
      root = nullptr;
    }

    BST (T value) {
      root = new bstNode<T>(value);
    }

    ~BST () {};
    void insert (T value) {
      bstNode<T> *node = new bstNode<T>(value);
      if (root == nullptr) {
        root = node;
        return;
      }
      if (find(value)) {
        cout << "Data already present:" << value << endl;
        return;
      }
      
      bstNode<T> *tmp = root;
      // iterate through the tree and insert it at current position
      while (tmp) {
        if (tmp->getData() > value) {
          // If data is less than current node then go left
          if (tmp->getLeft() == nullptr) {
            tmp->setLeft(node);
            return;
          }
          tmp = tmp->getLeft();
        } else if (tmp->getData() < value) {
          // if data is greater than current node then go right
          if (tmp->getRight() == nullptr) {
            tmp->setRight(node);
            return;
          }
          tmp = tmp->getRight();
        }
      }

      return;     
    }

    void remove (T value) {
      if (root == nullptr) {
        cout << "BST is empty" << endl;
        return;
      }

      bstNode<T> *tmp = root;
      bstNode<T> *parent = root;
      while(tmp) {
        if (tmp->getData() == value) {
          return deleteNode(tmp, parent);
        }
        if (tmp->getData() > value) {
          parent = tmp;
          tmp = tmp->getLeft();
        } else {
          parent = tmp;
          tmp = tmp->getRight();
        }
      }
      cout << "Data is not present:" << value << endl;
      return;
    }

    void print () {
      cout << "Inorder: ";
      printInOrder(root);
      cout << endl;
      cout << "PreOrder: ";
      printPreOrder(root);
      cout << endl;
      cout << "PostOrder: ";
      printPostOrder(root);
      cout << endl;
      return;
    }

    void printInOrder (bstNode<T> *node) {
      if (node ==  nullptr) {
        return;
      }
      printInOrder(node->getLeft());
      cout << node->getData() << " "; 
      printInOrder(node->getRight());
      return;
    }

    void printPreOrder (bstNode<T> *node) {
      if (node ==  nullptr) {
        return;
      }
      cout << node->getData() << " "; 
      printPreOrder(node->getLeft());
      printPreOrder(node->getRight());
      return;
    }

    void printPostOrder (bstNode<T> *node) {
      if (node ==  nullptr) {
        return;
      }
      
      printPostOrder(node->getLeft());
      printPostOrder(node->getRight());
      cout << node->getData() << " "; 
      return;
    }

    bool find (int value) {
      if (root == nullptr)
        return false;

      bstNode<T> *tmp = root;
      while (tmp) {
        if (tmp->getData() == value) {
          cout << "found:" << tmp->getData() << endl;
          return true;
        }
        if (tmp->getData() > value) {
          tmp = tmp->getLeft();
        } else {
          tmp = tmp->getRight();
        }
      }
      cout << "Not Found: " << value << endl;
      return false;
    }

    T findMin () {
      T ret{0};
      if (root == nullptr) {
        cout << "BST is empty" << endl;
        return ret;
      }
      bstNode<T> *tmp = root;
      while (root) {
        if (tmp->getLeft() == nullptr) {
          return tmp->getData();
        }
        tmp = tmp->getLeft();
      }
      return ret;
    }

    T findMax () {
      T ret{0};
      if (root == nullptr) {
        cout << "BST is empty" << endl;
        return ret;
      }
      bstNode<T> *tmp = root;
      while (root) {
        if (tmp->getRight() == nullptr) {
          return tmp->getData();
        }
        tmp = tmp->getRight();
      }
      return ret;
    }

    int findDepth () {
      return maxDepth(root);
    }

    void dfs () {
      return;
    }

    //
    // BFS implementation
    // Using queue to remeber the node to be visited
    //
    void bfs () {
      queue<bstNode<T>*> q;
      q.push(root);
      //iterarte through tree
      while (!q.empty()) {
        bstNode<T> *tmp = q.front();
        q.pop();
        cout << " " << tmp->getData();
        if (tmp->getLeft()) {
          // push the left node in queue for refernece 
          q.push(tmp->getLeft());
        }
        if (tmp->getRight()) {
          // push the left node in queue for refernece 
          q.push(tmp->getRight());
        }
      }
      return;
    }

  private:
    bstNode<T> *root;

    int maxDepth (bstNode<T> *root) {
      if (root == nullptr) {
        return 0;
      }
      return max(maxDepth(root->getLeft()), maxDepth(root->getRight())) + 1;
    }

    void deleteNode (bstNode<T> *node, bstNode<T> *parent) {
      //cout << "deleting:" << node->getData() << " parent:" << parent->getData() << endl;
      if (node->getLeft() == nullptr && node->getRight() == nullptr) {
        // leaf node
        if (parent == nullptr) {
          root = nullptr;
        } else {
          if (parent->getLeft() == node) {
            // left child
            parent->setLeft(nullptr);
          } else {
            // right child
            parent->setRight(nullptr);
          }
        }
        free(node);
      } else {
        if (node->getLeft() == nullptr) {
          // only right child
          if (parent->getLeft() == node) {
            parent->setLeft(node->getRight());
          } else {
            parent->setRight(node->getRight());
          }
          free(node);
        } else if (node->getRight() == nullptr) {
          // only left child
          if (parent->getLeft() == node) {
            parent->setLeft(node->getLeft());
          } else {
            parent->setRight(node->getLeft());
          }
          free(node);
        } else {
          // node has both children
          // Find the min of right subtree, replace
          // data of node with it and delete the leaf node
          bstNode<T> *tmp = node->getRight();
          parent = node;
          while(tmp != nullptr) {
            if (tmp->getLeft() == nullptr) {
              break;
            }
            parent = tmp;
            tmp = tmp->getLeft();
          }
          node->setData(tmp->getData());
          return deleteNode(tmp, parent);
        }
      }
      return;
    }
 };
