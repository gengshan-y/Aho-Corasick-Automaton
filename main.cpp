#include <iostream>
#include "ACNode.hpp"
#include "ACAutomaton.hpp"
#include "ACAutomaton.cpp"  // should link .cpp since constructor in it

using namespace std;

int main() {
  ACAutomaton* ACT = new ACAutomaton();
  ACT->insert("he");
  ACT->insert("she");
  ACT->insert("his");
  ACT->insert("hers");
  ACT->build();
  ACT->match("ushers");
  ACT->print();
  return 0;
}
