#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>

class Expression{
 public:
  virtual std::string toString() const = 0;
  virtual long evaluate() const = 0;
};

class Operator : public Expression{
 protected:
  Expression * lhs;
  Expression * rhs;
  std::string opStr;
 public:
  virtual std::string toString() const{
    std::stringstream ss;
    ss << "(" << lhs->toString() << opStr << rhs->toString() << ")";
    return ss.str();
  }
  virtual long evaluate() const = 0;
};

class NumExpression : public Expression{
 private:
  long value;
 public:
 NumExpression(long v): value(v){}
  virtual std::string toString() const{
    std::stringstream ss;
    ss << value;
    return ss.str();
  }
  virtual long evaluate() const{
    return value;
  }
};

class PlusExpression : public Operator{
 public:
  PlusExpression(Expression * l, Expression * r){
    lhs = l;
    rhs = r;
    opStr = " + ";
  }
  virtual long evaluate() const{
    long lValue = lhs->evaluate();
    long rValue = rhs->evaluate();
    return (lValue + rValue);
  }
};

class MinusExpression : public Operator{
 public:
  MinusExpression(Expression * l, Expression * r){
    lhs = l;
    rhs = r;
    opStr = " - ";
  }
  virtual long evaluate() const{
    long lValue = lhs->evaluate();
    long rValue = rhs->evaluate();
    return (lValue - rValue);
  }
};

class TimesExpression : public Operator{
 public: 
  TimesExpression(Expression * l, Expression * r){
    lhs = l;
    rhs = r;
    opStr = " * ";
  }
  virtual long evaluate() const{
    long lValue = lhs->evaluate();
    long rValue = rhs->evaluate();
    return (lValue * rValue);
  }
};

class DivExpression : public Operator{
 public: 
  DivExpression(Expression * l, Expression * r){
    lhs = l;
    rhs = r;
    opStr = " / ";
  }
  virtual long evaluate() const{
    long lValue = lhs->evaluate();
    long rValue = rhs->evaluate();
    return (lValue / rValue);
  }
};
