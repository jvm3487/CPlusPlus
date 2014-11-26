#ifndef _LL_H_
#define _LL_H_
#include <cstdlib>
#include <exception>
#include <assert.h>
#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <cstring>
#include "function.h"
#include <vector>
#include <utility>

class outOfBounds: public std::exception{};

template<typename T>
class LinkedList {
 private:
  class Node{
   private:
    T data;
    Node * next;
    Node * previous;
   public:
    ~Node(){    }
    Node(): data(NULL), next(NULL), previous(NULL) {}
    Node(const T & item): data(item), next(NULL), previous(NULL) {}
    Node(const Node & rhs){
      data = rhs.data;
      next = rhs.next;
      previous = rhs.previous;
    }
    Node & operator=(const Node & rhs){
      if (this != &rhs){
	data = rhs.data;
	next = rhs.next;
	previous = rhs.previous;
      }
      return *this;
    }
    friend class LinkedList<T>;
  };
  Node * front;
  Node * back;
 public:
  LinkedList(): front(NULL), back(NULL) {}
  ~LinkedList(){
    if (front != NULL){
      Node * temp = front;
      Node * temp2 = front;
      while (temp->next != NULL){
	temp2 = temp;
	temp = temp->next;
	destroy(temp2);
      }
      destroy(temp);
    }
  }
  void addFront(const T &item){
    Node * newNode = new Node(item);
    if (newNode == NULL){
      destroy(newNode);
      return;
    }
    newNode->previous = NULL;
    newNode->next = front;
    front = newNode;
    if (back == NULL){
      back = newNode;
    }
    else{
      newNode->next->previous = newNode;
    }
  }
  void addBack(const T &item){
    Node * newNode = new Node(item);
    if (newNode == NULL){
      destroy(newNode);
      return;
    }
    newNode->previous = back;
    newNode->next = NULL;
    back = newNode;
    if (front == NULL){
      front = newNode;
    }
    else{
      newNode->previous->next = newNode;
    }
  }
  bool remove(const T &item){
    if (front == NULL){
      return false;
    }
    if (front->data == item){
      destroy(front);
      return true;
    }
    Node * temp = front;
    while (temp->next != NULL){
      if (temp->next->data == item){
	destroy(temp->next);
	return true;
      }
      temp = temp->next;
    }
    return false;
  }
  void destroy(Node * toDest){
    if (toDest == NULL){
      return;
    }
    if (toDest->previous == NULL){
      Node * temp = front;
      if(toDest->next != NULL){
	front = toDest->next;
	toDest->next->previous = NULL;
      }
      else{
	front = NULL;
	back = NULL;
      }
      delete temp;
      return;
    }
    if (toDest->next == NULL){
      Node * temp = back;
      if (toDest->previous != NULL){
	back = toDest->previous;
	toDest->previous->next = NULL;
      }
      delete temp;
      return;
    }
    Node * temp = toDest;
    toDest->previous->next = toDest->next;
    toDest->next->previous = toDest->previous;
    delete temp;
    return;
  }
  T& operator[](int index){
    try{
      if (front == NULL){
	throw outOfBounds();
      }
      if (index == 0){
	return front->data;
      }
      Node * temp = front;
      int elementCounter = 1;
      while (temp->next != NULL){
	if (index == elementCounter){
	  return temp->next->data;
	}
	elementCounter++;
	temp = temp->next;
      }	
      throw outOfBounds();
    }
    catch(std::exception & e){
      std::cout << "It's just too much!!" << std::endl;
      return (*this)[index-1];
    }
  }
  T& operator[](int index) const{
    try{
      if (front == NULL){
	throw outOfBounds();
      }
      if (index == 0){
	return front->data;
      }
      Node * temp = front;
      int elementCounter = 1;
      while (temp->next != NULL){
	if (index == elementCounter){
	  return temp->next->data;
	}
	elementCounter++;
	temp = temp->next;
      }
      throw outOfBounds();
    }
    catch(std::exception & e){
      std::cout << "It's just too much!!" << std::endl;
      return (*this)[index-1];
    }
  }
  int find(const T &item) const{ 
    if (front == NULL){
      return -1;
    }
    if (item == front->data){
      return 0;
    }
    Node * temp = front;
    int elementCounter = 1;
    while (temp->next != NULL){
      if (item == temp->next->data){
	return elementCounter;
      }
      elementCounter++;    
      temp = temp->next;
    }
    return -1;
  }  
  int getSize() const{
    Node * temp = front;
    int counter = 1;
    if (temp == NULL){
      return 0;
    }
    while (temp->next != NULL){
      temp = temp->next;
      counter ++;
    }
    return counter;
  }
  LinkedList(const LinkedList & rhs){
    if (rhs.front == NULL){
      front = NULL;
      back = NULL;
      return;
    }
    front = new Node(*(rhs).front);
    front->next = NULL;
    back = front;
    if (rhs.front->next != NULL){
      Node * temp = rhs.front;
      while (temp->next != NULL){
	this->addBack(temp->next->data);
	temp = temp->next;
      }
      back = temp;
    }
  }
  LinkedList & operator=(const LinkedList & rhs){
    if (this != &rhs){
      this->~LinkedList();
      if (rhs.front == NULL){
	front = NULL;
	back = NULL;
	return *this;
      }
      front = new Node(*(rhs).front);
      front->next = NULL;
      back = front;
      if (rhs.front->next != NULL){
	Node * temp = rhs.front;
	while (temp->next != NULL){
	  this->addBack(temp->next->data);
	  temp = temp->next;
	}
	back = temp;
      }
    }
    return *this;
  }
  void app(Function<void,const T&> * f) const{
    if (front == NULL){
      return;
    }
    f->invoke(front->data);
    Node * temp = front;
    while (temp->next != NULL){
      f->invoke(temp->next->data);
      temp = temp->next;
    }
  }
  void update(Function<T, const T&> * f){
    if (front == NULL){
      return;
    }
    front->data = f->invoke(front->data);
    Node * temp = front;
    while (temp->next != NULL){
      temp->next->data = f->invoke(temp->next->data);
      temp = temp->next;
    }
  }
  template<typename R>
  LinkedList<R> * map(Function<R,const T&> * f) const{
    LinkedList<R> * johnIsAwesome = new LinkedList<R>();
    if (front == NULL){
      return johnIsAwesome;
    }
    johnIsAwesome->addBack(f->invoke(front->data));
    Node * temp = front;
    while (temp->next != NULL){
      johnIsAwesome->addBack(f->invoke(temp->next->data));
      temp = temp->next;
    }
    return johnIsAwesome;
  }
  void filter(Function<bool, const T&> * f){
    if (front == NULL){
      return;
    }
    if (f->invoke(front->data) == false){
      destroy(front);
      this->filter(f);
    }
    else{
      Node * temp = front;
      while (temp->next != NULL){
	if (f->invoke(temp->next->data) == false){
	  destroy(temp->next);
	}   
	else{
	  temp = temp->next;
	}
      }
    }
  }
  std::vector<LinkedList<T> > split(Function<unsigned, const T&> * f) const{
    std::vector<LinkedList<T> > huhQuest;
    int currentSize = 0;
    if (front == NULL){
      return huhQuest;
    }
    int currentValue = f->invoke(front->data);
    if (currentValue > currentSize-1){
      currentSize = currentValue + 1;
      huhQuest.resize(currentSize);
    }
    huhQuest[currentValue].addBack(front->data);
    Node * temp = front;
    while (temp->next != NULL){
      currentValue = f->invoke(temp->next->data);
      if (currentValue > currentSize-1){
	currentSize = currentValue + 1;
	huhQuest.resize(currentSize);
      }
      huhQuest[currentValue].addBack(temp->next->data);
      temp = temp->next;
    }
    return huhQuest;
  }
  template<typename R>
  R foldl (Function<R, std::pair<const T&,const R&> > * f, const R& start){
    R answer = start;
    if (front == NULL){
      return answer;
    }
    answer = f->invoke(std::pair<const T&,const R&>(front->data, answer));
    Node * temp = front;
    while (temp-> next != NULL){
      answer = f->invoke(std::pair<const T&,const R&>(temp->next->data, answer));
      temp = temp->next;
    }
    return answer;
  }
};
  
#endif
