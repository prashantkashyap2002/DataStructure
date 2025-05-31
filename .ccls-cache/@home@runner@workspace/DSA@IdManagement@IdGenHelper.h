
#include <atomic>
#include <bits/stdc++.h>
#include <iostream>
using namespace std;

// Id Space = 2^32
constexpr long int idSpaceSize = 4294967296;
constexpr int bucketSize = 4096;
constexpr int numBucket = idSpaceSize / bucketSize;
constexpr int asciiListSize = 128;

// 2 sec cooling time for id to be available again after deletion
constexpr int coolingTime = 2;
std::atomic<bool> _running;

struct TrieOpaqNode;
typedef struct TrieOpaqNode *TrieOpaqNodePtr;
struct TrieOpaqNode {
  std::vector<TrieOpaqNodePtr> children;
  bool isLeaf;
  int refCnt;
  std::string _data = "";
  int id = -1;

  TrieOpaqNode() : children(asciiListSize, nullptr), isLeaf(false), refCnt(0) {}

  const char *getData() {
    if (_data == "")
      return nullptr;
    // std::cout << "data:" << _data << std::endl;
    return _data.data();
  }

  void setData(const std::string &data) {
    _data = data;
    // std::cout << "data:" << _data << std::endl;
    return;
  }

  void increamentRefCnt() {
    refCnt++;
    return;
  }

  void decreamentRefCnt() {
    refCnt--;
    return;
  }

  int getRefCnt() { return refCnt; }
  void setLeaf(bool value) { isLeaf = value; }
  bool getLeaf() { return isLeaf; }
  void setId(int value) { id = value; }
  int getId() { return id; }
};

class TrieOpaq {
public:
  TrieOpaq() { root = new TrieOpaqNode(); }
  ~TrieOpaq() { delete root; }

  void insertOpaqData(const std::string &data) {
    TrieOpaqNodePtr current = root;

    for (auto c : data) {
      int index = c - ' ';
      if (!current->children[index]) {
        current->children[index] = new TrieOpaqNode();
      }
      current = current->children[index];
    }
    current->setLeaf(true);
    current->setData(data);
    current->increamentRefCnt();
  }

  bool searchOpaqData(const std::string &data) {
    TrieOpaqNodePtr current = root;
    for (auto c : data) {
      int index = c - ' ';
      if (!current->children[index]) {
        return false;
      }
      current = current->children[index];
    }
    return current != nullptr && current->getLeaf();
  }

  TrieOpaqNodePtr getOpaqData(const std::string &data) {
    TrieOpaqNodePtr current = root;
    for (auto c : data) {
      int index = c - ' ';
      if (!current->children[index]) {
        return nullptr;
      }
      current = current->children[index];
    }
    return current != nullptr && current->getLeaf() ? current : nullptr;
  }

  void removeOpaqData(const std::string &data) {
    if (root == nullptr) {
      std::cout << "Trie is empty" << std::endl;
      return;
    }

    TrieOpaqNodePtr current = root;
    TrieOpaqNodePtr parent = root;
    for (auto c : data) {
      int index = c - ' ';
      if (!current->children[index]) {
        std::cout << "data not found" << std::endl;
        return;
      }
      parent = current;
      current = current->children[index];
    }

    if (current != nullptr && current->getLeaf()) {
      current->decreamentRefCnt();
      if (current->getRefCnt() == 0) {
        current->setLeaf(false);
        current->setData("");
        current->setId(-1);
        int i = 0;
        for (; i < asciiListSize; i++) {
          // check if there is any child to this node. If not then we can delete
          // the node
          if (current->children[i] != nullptr) {
            break;
          }
        }
        if (i == asciiListSize) {
          // no child the current node so safe to delete the node and set
          // nullptr to parent
          delete current;
          parent->children[data.back() - ' '] = nullptr;
          // cout << "deleted node:" << data << endl;
        }
      }
    }
    return;
  }

private:
  // trie root node
  TrieOpaqNodePtr root;
};