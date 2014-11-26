#ifndef __BSTMAP_H__
#define __BSTMAP_H__
#include <cstdlib>
#include "map.h"
#include <iostream>

template<typename K, typename V>
class BstMap : public Map<K,V>{
 private:
  class Node{
  public:
    K keyN;
    V valueN;
    Node * left;
    Node * right;
    Node(): keyN(K()), valueN(V()), left(NULL), right(NULL){}
    Node(const K & key, const V & value): keyN(key), valueN(value), left(NULL), right(NULL){} 
  };
  Node * root;
 public:
  BstMap(): root(NULL){}
  ~BstMap(){
    Node ** temp = &root;
    while (*temp != NULL){
      remove((*temp)->keyN);
    }
  }
  virtual void add(const K & key, const V & value){
    Node * toAdd = new Node(key,value);
    //std::cout << "Allocate!" << std::endl;
    Node ** temp = &root;
    while ((*temp) != NULL){
      if (key == (*temp)->keyN){
	remove(key);
	delete toAdd;
	add(key,value);
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
  virtual const V & lookup(const K & key) const throw (std::invalid_argument){
    Node * const * temp = &root;
    while (*temp != NULL){
     if ((*temp)->keyN == key){
       return (*temp)->valueN;
     }
     if (key < (*temp)->keyN){
       temp = &(*temp)->left;
     }
     else{
       temp = &(*temp)->right;
     }
   }
   throw std::invalid_argument("The key doesn't exist!");
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
	//std::cout << "delete1!" <<std::endl;
	return temp;
      }
      if (curr->right == NULL){
	Node * temp = curr->left;
	delete curr;
	//std::cout << "delete2!" <<std::endl;
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
