#include <iostream>
#include <cstring>


/*
ghazi abbas
c++/ds DC galbraith
spring sem

binary expression tree


Sources:
prof. Fant lectures on mr galbraiths canvas page
+
https://www.youtube.com/watch?v=_LxbhLNRZkI
https://www.youtube.com/watch?v=BHB0B1jFKQc
https://www.youtube.com/watch?v=om1C190DfPc
https://www.youtube.com/watch?v=WLvU5EQVZqY 


*/
using namespace std;
//node struct w both left/right pointers
struct Node
{
  int data;
  Node* left;
  Node* right;
};
//class stacxk according to prof fants lecture
class Stack
{
public:
  
  Stack();
  ~Stack();
  int push(const char&);
  int pop(char&);
  int peek(char&);
  int isEmpty();
  int isFull();
  int print();

private:
  static const int SIZE = 100;
  char* arr;
  int top;
};
//stack class according to lecture
class Queue
{
 public:
  Queue();
  ~Queue();
  int enqueue(const char&);
  int dequeue(char&);
  int peek(char&);
  int isEmpty();
  int isFull();
private:
  static const int SIZE = 100;
  char* arr;
  int front;
  int rear;
};




















int main()
{


}

//constructor and destructor, intiializing 
Stack::Stack()
{
  arr= new char[SIZE];
  top = -1;
}
Stack::~Stack()
{
  delete[] arr;
}


//push and pop, explained by lecture and a different video
int Stack::push(const char& item)
{
  if(isFull())
    {
      return -1;
    }

  arr[++top] = item;
  return 0;
}
int Stack::pop()
{
  if(isEmpty())
    {
      return -1;
    }
  item = arr[top--];
  return 0;
}

int Stack::peek(char& item)
{
  if(isEmpty())
    {
      return -1;
    }
  
}

