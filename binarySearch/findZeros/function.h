#ifndef __FUNCTION_H__
#define __FUNCTION_H__
#include <math.h>
#include <iostream>

template<typename R, typename A> 
class Function {
public:
  virtual R invoke(A arg) = 0;
  virtual ~Function() {}
};

template<typename R, typename A>
class SinFunction : public Function<int, int> {
public:
  virtual int invoke(int arg) {
    std::cout << "CountME" << std::endl;
    return 10000000 * (sin(arg/100000.0) - 0.5);
  }
};
#endif
