#include "node.h"
#include <iostream>
void Node::buildMap(BitString b, std::map<unsigned,BitString> & theMap) {
  BitString c;
  c.append(b);
  if (left->sym != NO_SYM){
    theMap[left->sym] = c.plusZero();
  }
  else{
    Node * tempLeft = left;
    Node * tempRight = right;
    left = left->left;
    right = tempLeft->right;
    buildMap(c.plusZero(), theMap);
    left = tempLeft;
    right = tempRight;
  }
  if (right->sym != NO_SYM){
    theMap[right->sym] = b.plusOne();
  }
  else{
    Node * tempLeft = left;
    Node * tempRight = right;
    left = right->left;
    right = tempRight->right;
    buildMap(b.plusOne(), theMap);
    left = tempLeft;
    right = tempRight;
  }
}


