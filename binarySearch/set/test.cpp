#include "bstset.h"
#include <cstdlib>
#include <string>
#include <iostream>

int main(){
  BstSet<std::string> johnsList;
  johnsList.add("John");
  johnsList.add("Trinh");
  johnsList.add("John Jr");
  johnsList.add("John");
  std::cout << johnsList.contains("Trinh") << std::endl;
  std::cout << johnsList.contains("John") << std::endl;
  std::cout << johnsList.contains("John Jr") << std::endl;
  std::cout << johnsList.contains("Not here!") << std::endl;
  return EXIT_SUCCESS;
}
