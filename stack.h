#ifndef STACK_H
#define STACK_H

using namespace std;

class Stack
{
 public:
  Stack();
  ~Stack();
  int push(const data&);
  int pop(data&);
  //type int Not returning type data literally
  int peek(data&);
  int isEmpty();
  int isFull();
  int print();
private:

};




#emdif
