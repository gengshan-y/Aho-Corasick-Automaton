#ifndef ACAutomaton_HPP
#define ACAutomaton_HPP

#include <string>
#include "ACNode.hpp"

class ACAutomaton{
 public:
  /** Constructor **/
  ACAutomaton();
  /** Destructor **/
  ~ACAutomaton();

  /** Get the size of the dictionary **/
  unsigned int GetSize();

  /** Insert a word to the trie, if succeed return true **/
  bool insert(string word);

  /** Build the transition edge **/
  void build();
  void match(string target);
  void print();

 private:
  ACNode* root;
  vector <pair <string, vector<int>>> patternPos;
  void destoryAll(ACNode* n);
};

#endif  // ACAutomaton_HPP
