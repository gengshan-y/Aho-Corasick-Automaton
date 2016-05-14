#include <iostream>
#include <queue>
#include <utility>
#include "ACAutomaton.hpp"

ACAutomaton::ACAutomaton() {
  root = new ACNode();
  root->failNode = root;
/*  
  for (int i = 0; i < CHAR_SIZE; i++) {
    root->nextNode[i] = root;
  }
*/
}

ACAutomaton::~ACAutomaton() {
  destoryAll(root);
}

bool ACAutomaton::insert(string word) {
  if (!word.size()) {
    std::cout << "Empty string!"  << std::endl;
    return false;
  }

  ACNode* tempNode = root;
  bool isInserted = false;
  int i = 0;

  while (word[i]) {
    if (!tempNode->nextNode[word[i]]) {  // if empty, add node
      if (!word[i+1]) {  // if at the end
        tempNode->nextNode[word[i]] = new ACNode();
        tempNode->nextNode[word[i]]->wordNum = patternPos.size();
      }
      else {
        tempNode->nextNode[word[i]] = new ACNode();
      }
      isInserted = true;
    }
    tempNode = tempNode->nextNode[word[i]];
    i++;
  }
  
  /* already at the leaf of the trie */
  if (tempNode->wordNum != -1) {
    tempNode->wordNum = patternPos.size();
    isInserted = true;
  }

  /* updata pattern-position pair */
  pair<string, vector<int>> tempPair(word, vector<int>());  // -1 position denotes null
  patternPos.push_back(tempPair);

  return isInserted;
}

void ACAutomaton::build() {
  queue<ACNode*> q;
  ACNode* tempNode;

  /** Set the depth 1 nodes **/
  for (int i = 0; i < CHAR_SIZE; i++) {
    if (root->nextNode[i]) {
      root->nextNode[i]->failNode = root;
      q.push(root->nextNode[i]);
    }
  }

  while (q.size()) {  // while queue is not empty
    tempNode = q.front();
    q.pop();
    for (int i = 0; i < CHAR_SIZE; i++) {
      if (tempNode->nextNode[i]) {
      /* push all the existing children */
        q.push(tempNode->nextNode[i]);
      /* set fail transition node for each childrenn */
        if (tempNode->failNode->nextNode[i] == 0)
          tempNode->nextNode[i]->failNode = root;
        else
          tempNode->nextNode[i]->failNode = tempNode->failNode->nextNode[i];
      }
    } 
  }

}

void ACAutomaton::match(string target) {
  if (!target.size()) {
    std::cout << "Empty string!"  << std::endl;
    return;
  }

  ACNode* tempNode = root;
  int i = 0;
  pair <string, vector <int>>* pattPosPair;

  while (target[i]) {
    if (tempNode->wordNum != -1) {
      pattPosPair = &(patternPos[tempNode->wordNum]);
      get<1>(*pattPosPair).push_back(i-get<0>(*pattPosPair).size());
    }
    if (tempNode->nextNode[target[i]]) {
      tempNode = tempNode->nextNode[target[i]]; 
    }
    else {
      tempNode = tempNode->failNode;
      if (tempNode != root)
        continue;
    }
    i++;
  }

  if (tempNode->wordNum != -1) {
    pattPosPair = &patternPos[tempNode->wordNum];
    get<1>(*pattPosPair).push_back(i-get<0>(*pattPosPair).size());
  }
}

void ACAutomaton::print() {
  for (auto it = patternPos.begin(); it != patternPos.end(); it++ ) {
    cout << get<0>(*it) << ":";
    for (unsigned i = 0; i < get<1>(*it).size(); i++) {
      cout << " " << get<1>(*it)[i];
    }
    cout << endl;
  }
}

void ACAutomaton::destoryAll(ACNode* n) {
  if (!n)
    return;
  /* delete all children first */
  for (int i = 0; i < CHAR_SIZE; i++) {
    destoryAll(n->nextNode[i]);
  }
  delete n;
}
