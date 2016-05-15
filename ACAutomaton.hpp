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
 
  /** Match the target with patterns in the trie **/
  void match(string target);
  
  /** Print the found pattern **/
  void print();

 private:
  ACNode* root;  // root of a multi-way search trie
  vector <pair <string, vector<int>>> patternPos;  // <pattern, positions> pair
  /** Destory subtrie n **/
  void destoryAll(ACNode* n);
};

#endif  // ACAutomaton_HPP
