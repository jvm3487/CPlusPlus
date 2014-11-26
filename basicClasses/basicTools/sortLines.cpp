#include<cstdlib>
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<fstream>

template<typename T>
std::ostream & operator<<(std::ostream & s, const std::vector<T> & v){
  for (unsigned i=0; i < v.size(); i++){
    s << v[i];
    if (i != v.size()-1){
      s << std::endl;
    }
  }
  return s;
}

int main(int argc, const char * argv[]){
  std::vector<std::string> lines;
  std::string typeIn;
  if (argc == 1){
    while(std::getline (std::cin, typeIn)){
      lines.push_back(typeIn);
    }
  }
  if (argc > 1){
    int i = 1;
    while (argv[i] != NULL){
      std::ifstream f (argv[i]);
      if (f == NULL){
	std::cerr << "This is not a vaiid file!" << std::endl;
	exit (EXIT_FAILURE);
      }
      while(std::getline (f, typeIn)){
	lines.push_back(typeIn);
      }
      i++;
    }
  }
  std::sort (lines.begin(), lines.end());
  std::cout << lines << std::endl;
  return EXIT_SUCCESS;
}
