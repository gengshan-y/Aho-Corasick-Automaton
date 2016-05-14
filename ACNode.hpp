#ifndef ACNODE_HPP
#define ACNODE_HPP

#include <set>
#include <vector>
#include <iostream>

#define CHAR_SIZE 256

using namespace std;

class ACNode {
 private:
  vector<ACNode*> nextNode;
  ACNode* failNode;
  int wordNum;

  ACNode() {
    nextNode = vector<ACNode*>(CHAR_SIZE, 0);
    failNode = 0;
    wordNum = -1;
  }

  friend class ACAutomaton;
};

#endif  // ACNODE_HPP
