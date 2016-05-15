#include <iostream>
#include <queue>
#include <utility>
#include "ACAutomaton.hpp"

ACAutomaton::ACAutomaton() {
  root = new ACNode();
  root->failNode = root;  // the sub-string of a "" is ""
}

ACAutomaton::~ACAutomaton() {
  destoryAll(root);
}

unsigned int ACAutomaton::GetSize() {
  return patternPos.size();
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
        // set num as the current size of pattern pair
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

  /* updata pattern-position pair, -1 position denotes null */
  pair<string, vector<int>> tempPair(word, vector<int>()); 
  patternPos.push_back(tempPair);

  return isInserted;
}

void ACAutomaton::build() {
  queue<ACNode*> q;
  ACNode* tempNode;
  ACNode* lastFail;

  /** Set the failpointer of depth 1 nodes **/
  for (int i = 0; i < CHAR_SIZE; i++) {
    if (root->nextNode[i]) {
      root->nextNode[i]->failNode = root;  // mismatch of "a" -> start from ""
      q.push(root->nextNode[i]);  // BFS to update failpointer
    }
  }

  while (q.size()) {  // while queue is not empty
    tempNode = q.front();
    q.pop();
    for (int i = 0; i < CHAR_SIZE; i++) {
      if (tempNode->nextNode[i]) {
      /* push all the existing children */
        q.push(tempNode->nextNode[i]);
      /* set fail pointer for each childrenn */
        lastFail = tempNode;
        /* calculate the longest sub-string */
        while (lastFail->failNode->nextNode[i] == 0 && lastFail != root)
          lastFail = lastFail->failNode;
        if (lastFail == root)  // if already have no substring
          tempNode->nextNode[i]->failNode = root;
        else
          tempNode->nextNode[i]->failNode = lastFail->failNode->nextNode[i];
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
  pair <string, vector <int>>* pattPosPair;  // temp pair to update patternPair

  while (target[i]) {
    /* check if pattern is found */
    if (tempNode->wordNum != -1) {  // is a pattern
      pattPosPair = &(patternPos[tempNode->wordNum]);
      get<1>(*pattPosPair).push_back(i-get<0>(*pattPosPair).size());
    }
    if (tempNode->nextNode[target[i]]) {
      tempNode = tempNode->nextNode[target[i]]; 
    }
    /* if tempNode is root, we have no substring for this pattern */
    else if (tempNode != root) {
      tempNode = tempNode->failNode;
      continue;  // dont move database string if fail
    }
    i++;
  }

  /* update the last pattern */
  if (tempNode->wordNum != -1) {
    pattPosPair = &patternPos[tempNode->wordNum];
    get<1>(*pattPosPair).push_back(i-get<0>(*pattPosPair).size());
  }
}

void ACAutomaton::print() {
  for (auto it = patternPos.begin(); it != patternPos.end(); it++ ) {
    cout << get<0>(*it) << ":";
    if (!get<1>(*it).size())  // havent found this pattern
      cout << " -1" << endl;
    else {
      for (unsigned i = 0; i < get<1>(*it).size(); i++)
        cout << " " << get<1>(*it)[i];
      cout << endl;
    }
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
