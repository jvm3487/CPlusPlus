#include <stdio.h>
#include <cstdlib>
#include "readFreq.h"
#include <iostream>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256 ) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  FILE * f = fopen(fname, "r");
  if (f == NULL){
    std::cerr << "The file does not exist" << std::endl;
    exit (EXIT_FAILURE);
  }
  uint64_t * charArray = new uint64_t[257];
  for (int i = 0; i < 257; i++){
    charArray[i] = 0;
  }
  int c;
  while ((c=fgetc(f)) != EOF){
    charArray[c]++;
  }
  charArray[256] = 1;
  fclose(f);
  return charArray;
}
