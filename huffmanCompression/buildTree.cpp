#include "node.h"
#include <iostream>

Node *  buildTree(uint64_t * counts) {
  priority_queue_t pq;
  for (int i = 0; i < 257; i++){
    if (counts[i] != 0){
      pq.push(new Node(i,counts[i]));
    }
  }
  while (pq.size() > 1){
    Node * temp = pq.top();
    pq.pop();
    Node * temp2 = pq.top();
    pq.pop();
    pq.push(new Node(temp, temp2));
  }
  return pq.top();
}  
