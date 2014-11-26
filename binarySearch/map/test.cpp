#include "bstmap.h"
#include <cstdlib>
#include <string>
#include <iostream>

int main(){
  BstMap<std::string, int> johnsList;
  johnsList.add("John", 2);
  johnsList.add("Trinh",1);
  johnsList.add("John Jr",3);
  johnsList.add("John",4);
  std::cout << johnsList.lookup("Trinh") << std::endl;
  std::cout << johnsList.lookup("John") << std::endl;
  std::cout << johnsList.lookup("John Jr") << std::endl;
  return EXIT_SUCCESS;
}
