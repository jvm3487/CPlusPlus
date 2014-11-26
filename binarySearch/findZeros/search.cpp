#include <cstdlib>
#include "function.h"
#include <iostream>
#include <math.h>

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (f->invoke(high) < 0){
    return high;
  }
  if (f->invoke(low) > 0){
    return low;
  }
  while (low != high){
    int mid = (low + high) / 2;
    int middleValue = f->invoke(mid);
    if (middleValue == 0){ return mid; }
    if (middleValue > 0){
      high = mid;
    }
    else{
      low = mid+1;
    }
  }
  return low;
}
