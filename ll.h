#ifndef __LL_H__
#define __LL_H__

#include <cstdlib>
#include <iostream>

class Ll{
 private:
  class Node{
   public:
    int data;
    Node * next; 
    Node(int d): data(d), next(NULL){}
  };
  Node * head;
 public:
  Ll(): head(NULL){}
  ~Ll(){
    Node * temp = head;
    while (temp != NULL){
      Node * del = temp;
      temp = temp->next;
      delete del;
    }
  }
  void addBack(int d){
    Node ** curr = &head;
    while ((*curr) != NULL){
      curr = &(*curr)->next;
    }
    Node * added = new Node(d);
    (*curr) = added;
  }
  void printList(){ 
    Node ** curr = &head;
    while ((*curr) != NULL){
      std::cout << (*curr)->data << " ";
      curr = &(*curr)->next;
    }
    std::cout << std::endl;
  }
  Ll * insertionSort(){
    Node ** curr = &head;
    Ll * ans = new Ll;
    if ((*curr) != NULL){
      ans->addBack((*curr)->data);
    }
    else{
      return ans;
    }
    while ((*curr) != NULL && (*curr)->next != NULL){ 
      if ((*curr)->next->data < (*curr)->data){
	Node * temp = ans->head;
	Node * add = new Node((*curr)->next->data);
	if (temp->data > (*curr)->next->data){ //checks if node should go in the front
	  add->next = ans->head;
	  ans->head = add;
	}
	else{
	  while ((*curr)->next->data > temp->next->data){ //locates where to insert node
	    temp = temp->next;
	  }
	  add->next = temp->next;
	  temp->next = add;
	}
      }
      else{
	ans->addBack((*curr)->next->data);
      }
      curr = &(*curr)->next;
    }
    return ans;
  }
};

#endif 
