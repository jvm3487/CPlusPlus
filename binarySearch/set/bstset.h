#ifndef __BSTSET_H__
#define __BSTSET_H__
#include <cstdlib>
#include "set.h"

template<typename K>
class BstSet : public Set<K>{
 private:
  class Node{
  public:
    K keyN;
    Node * left;
    Node * right;
    Node(): keyN(K()), left(NULL), right(NULL){}
    Node(const K & key): keyN(key), left(NULL), right(NULL){} 
  };
  Node * root;
 public:
  BstSet(): root(NULL){}
  ~BstSet(){
    Node ** temp = &root;
    while (*temp != NULL){
      remove((*temp)->keyN);
    }
  }
  virtual void add(const K & key){
    Node * toAdd = new Node(key);
    Node ** temp = &root;
    while ((*temp) != NULL){
      if (key == (*temp)->keyN){
	remove(key);
	delete toAdd;
	add(key);
	return;
      }
      if(key < (*temp)->keyN){
	temp = & ((*temp)->left);
      }
      else{
	temp = & ((*temp)->right);
      }
    }
    *temp = toAdd;
  }
  virtual bool contains(const K&key) const{
    Node * const * temp = &root;
    while (*temp != NULL){
      if ((*temp)->keyN == key){
	return true;
      }
      if (key < (*temp)->keyN){
	temp = &(*temp)->left;
      }
      else{
	temp = &(*temp)->right;
      }
    }
    return false;
  }
  virtual void remove(const K & key){
    root = remove(root, key);
  }
  Node * remove(Node * curr, const K & key){
    if (curr == NULL){
      return NULL;
    }
    if (curr->keyN == key){
      if (curr->left == NULL){
	Node * temp = curr->right;
	delete curr;
	return temp;
      }
      if (curr->right == NULL){
	Node * temp = curr->left;
	delete curr;
	return temp;
      }
      curr = curr->left;
      while (curr->right != NULL){
	curr = curr->right;
      }
      Node * temp = curr;
      remove(curr->keyN);
      return temp;
    }
    else if (key < curr->keyN){
      curr->left = remove(curr->left, key);
    }
    else{
      curr->right = remove(curr->right, key);
    }
    return curr;
  }
};


#endif
