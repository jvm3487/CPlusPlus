#include <cstdlib>
#include <iostream>
#include "ll.h"

void swap(int * list, int first, int second){
  int temp = list[first];
  list[first] = list[second];
  list[second] = temp;
}

void bubbleSort(int * list, int length){
  for (int i = 0; i < length - 1; i ++){
    for (int j =0; j < length - 1 - i; j++){
      if (list[j+1] < list[j]){
        swap(list, j, j+1);
      }
    }
  }
}

void selectionSort(int * list, int length){
  for (int i = 0; i < length - 1; i++){
    int min = list[i];
    int minIndex = i;
    for (int j = i; j < length - 1; j++){
      if (min > list[j+1]){
        min = list[j+1];
        minIndex = j+1;
      }
    }
    if (minIndex != i){
      swap(list, minIndex, i);
    }
  }
}

void bubbleUp(int * list, int index, int parentI){
  if (parentI < 0){
    return;
  }
  if (list[index] > list[parentI]){
    swap(list, index, parentI);
    int newPar = (parentI-1)/2;
    bubbleUp(list, parentI, newPar);
  }
}

	
