#include "function.h"
#include <cstdlib>
#include <iostream>
#include "search.cpp"

int main(){
  SinFunction<int, int> g;
  int finish = binarySearchForZero(&g, 0, 150000);
  std::cout << finish << std::endl;
  return EXIT_SUCCESS;
}
