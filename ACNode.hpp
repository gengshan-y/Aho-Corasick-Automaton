#ifndef ACNODE_HPP
#define ACNODE_HPP

#include <vector>
#include <iostream>

#define CHAR_SIZE 256

using namespace std;

class ACNode {
 private:
  vector<ACNode*> nextNode;  // pointers to next nodes of a MWTrie
  ACNode* failNode;  // pointing to the last "correct" state
  int wordNum;  // number indicating a pattern stored in the trie

  ACNode() {
    nextNode = vector<ACNode*>(CHAR_SIZE, 0);
    failNode = 0;
    wordNum = -1;
  }

  friend class ACAutomaton;
};

#endif  // ACNODE_HPP
