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

void bubbleDown(int * list, int index, int length){
  int leftchild = index*2+1;
  if (leftchild > length-1){
    return;
  }
  if (leftchild == length - 1){
    if (list[leftchild] > list[index]){
      swap(list, leftchild, index);
    }
  }
  else{
    int rightchild = index*2+2;
    int swapI = (list[leftchild] > list[rightchild] ? leftchild : rightchild);
    if (list[swapI] > list[index]){
      swap(list, swapI, index);
      bubbleDown(list, swapI, length);
    }
  }
} 

void heap(int * list, int length){
  for (int i = 1; i < length; i++){
    int parentI = (i-1)/2;
    bubbleUp(list, i, parentI);
  }
}

void heapSort(int * list, int length){
  for (int i = length - 1; i > 0; i--){
    swap(list, 0, i);
    bubbleDown(list, 0, i);
  }
}

int * mergeSort(int * list, int length){
  int * ans = new int[length];
  int half = length / 2;
  if (half < 1){
    ans[0] = list[0];
    return ans;
  }
  int * lowerhalf = mergeSort(list, half);
  int * upperhalf = mergeSort(list + half,length-half);
  int lindex = 0;
  int uindex = 0;
  int current = 0;
  while (lindex != half && uindex != length-half){
    if (lowerhalf[lindex] < upperhalf[uindex]){
      ans[current] = lowerhalf[lindex];
      lindex++;
    }
    else{
      ans[current] = upperhalf[uindex];
      uindex++;
    }
    current++;
  }
  while (lindex != half){
    ans[current] = lowerhalf[lindex];
    lindex++;
    current++;
  }
  while (uindex != length-half){
    ans[current] = upperhalf[uindex];
    uindex++;
    current++;
  }
  delete[] lowerhalf;
  delete[] upperhalf;
  return ans;
}

void quickSort(int * list, int length){
  int pivot = rand() % length;
  swap(list, pivot, length-1);
  int left = 0;
  int right = length - 2;
  while (left <= right){
    if (list[left] > list[length-1] && list[right] <= list[length-1]){
      swap(list, left, right);
      left++;
      right--;
    }
    else if (list[left] <= list[length-1]){
      left++;
    }
    else{
      right--;
    }
  }
  swap(list, left, length-1);
  if (left > 1){
    quickSort(list, left);
  }
  if (length-left-1>1){
    quickSort(list+left+1, length-left-1);
  }
}

int * ranPseudo(int length){
  int * ans = new int[length];
  for (int i=0; i < length; i++){
    ans[i] = rand() % 100;
  }
  return ans;
}

void printList(int * list, int length){
  for (int i=0; i < length; i++){
    std::cout << list[i] << " ";
  }
  std::cout << std::endl;
}

int * generateUn(int length){ //generates an array of pseudo random numbers and prints it out
  std::cout << "Unsorted List" << std::endl;
  int * list = ranPseudo(length);
  printList(list, length);
  return list;
}

int main(){
  int * unsorted = generateUn(7);
  std::cout << "Bubble Sort" << std::endl;
  bubbleSort(unsorted, 7);
  printList(unsorted, 7);
  delete[] unsorted;
  int * unsorted2 = generateUn(8);
  std::cout << "Selection Sort" <<std::endl;
  selectionSort(unsorted2, 8);
  printList(unsorted2, 8);
  delete[] unsorted2;
  int * unsorted3 = ranPseudo(9);
  Ll unsor3;
  for (int i = 0; i < 9; i++){
    unsor3.addBack(unsorted3[i]);
  }
  std::cout << "Unsorted List" << std::endl;
  unsor3.printList();
  Ll * sort3 = unsor3.insertionSort();
  std::cout << "Insertion Sort" << std::endl;
  sort3->printList();
  delete[] unsorted3;
  delete sort3;
  int * unsorted4 = generateUn(11);
  std::cout << "Heap" << std::endl;
  heap(unsorted4, 11);
  printList(unsorted4, 11);
  std::cout << "Heap Sort" << std::endl;
  heapSort(unsorted4, 11);
  printList(unsorted4, 11);
  delete[] unsorted4;
  int * unsorted5 = generateUn(23);
  std::cout << "Merge Sort" <<std::endl;
  int * sorted5 = mergeSort(unsorted5, 23);
  printList(sorted5, 23);
  delete[] unsorted5;
  delete[] sorted5;
  int * unsorted6 = generateUn(14);
  std::cout << "Quick Sort" <<std::endl;
  quickSort(unsorted6, 14);
  printList(unsorted6, 14);
  delete[] unsorted6;
  return EXIT_SUCCESS;
}	
