#include <iostream>
#include <cstring>
#include <cctype>

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
  char data;
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
  //int print();
  int top;

private:
  static const int SIZE = 100;
  char* arr;
  
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

//fxn prototypes
bool isOp(char c); //check if char is operator
int getPrecedence(char c);//get an operators precedence
void InfixtoPostfix(const char* in, char* post, Stack& s, Queue& q);//convert infix expression to postfix
Node* createExpTree(Queue& q);
void traverseInorder(Node* r); //travers tree inorder, passes in the root ptr
void traversePreorder(Node* r);
void traversePostorder(Node* r);



int main()
{//prompts, drver code, output
  char infix[100];
  char postfix[100];
  cout << "Enter infix expression: ";
  cin.getline(infix, 100);

  Stack stack;
  Queue queue;
  
  InfixtoPostfix(infix, postfix, stack, queue);
  cout << "Postfix expression: " << postfix << endl;

  Node* root = createExpTree(queue);
  cout << "Infix expression: ";
  traverseInorder(root);
  cout << endl;

  cout << "Prefix expression: ";
  traversePreorder(root);
  cout << endl;

  cout << "Postfix expression: ";
  traversePostorder(root);
  cout << endl;

  return 0;
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


//push and pop, explained by lecture and a different video.   error handlign??
int Stack::push(const char& item)
{
  if(isFull())
  {
    return -1;
  }

  arr[++top] = item;
  return 0;
}
int Stack::pop(char& item)
{
  if(isEmpty())
  {
    return -1;
  }
  return arr[top--];
}
int Stack::peek(char& item)
{
  if(isEmpty())
  {
    return -1;
  }
  
  item = arr[top];
  return 0;
}

int Stack::isEmpty()
{
  return top == -1; //simplest implementations
}
int Stack::isFull()
{
  return top == SIZE-1;
}
/*
int Stack::print()
{
  if(isEmpty())
  {
    cout << "empty stack" << endl;
    return -1;
  }
  for(int x = top; x >= 0; --x)
  {
   cout << arr[x] << " ";
  }
  return 0;
}*/

//queue class implementations

// constr+destructor
Queue::Queue()
{
  arr = new char[SIZE];
  front = -1;
  rear = -1;
}
Queue::~Queue()
{
  delete[] arr;
  
}

//dequeue and enqueue explained by prof fant
int Queue::enqueue(const char& item)
{
  if(isFull())
  {
    return -1;
  }
  if(isEmpty())
  {
    front =0;
  }
  arr[++rear] = item;
  return 0;
}

int Queue::dequeue(char& item)
{
  if(isEmpty())
    {
      return -1;
    }
  item = arr[front];
  //front>rear wasnt progressing front
  if(front == rear)
  {
    front = rear = -1;
  }
  else
  {
    front++;
  }
  return 0;
}

int Queue::peek(char& item)
{
  if(isEmpty())
    {return-1;}
  item = arr[front];
  return 0;
}

int Queue::isEmpty()
{
  return front == -1;
}
int Queue::isFull()
{
  return rear == SIZE-1;
}

//fxn not in a class
bool isOp(char c)
{
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}
int getPrecedence(char c)
{
  if (c == '^') 
  {
    return 3;
  } else if (c == '*' || c == '/') 
  {
    return 2;
  } else if (c == '+' || c == '-') 
  {
    return 1;
  } else 
  {
    return 0; // Non-operators have a neutral precedence of 0
  }
}
void InfixtoPostfix(const char* in, char* post, Stack& s, Queue& q) //fixing funbction calls and operators
{//convert infix expression to postfix expr. 
int i = 0;
  while (in[i] != '\0') 
  {
    char current = in[i];
    if (isalnum(current)) 
    { // Operand
      q.enqueue(current);
    } else if (current == '(') 
    {
      s.push(current);
    } else if (current == ')') 
    {
      char topOperator;
      while (s.peek(topOperator) == 0 && topOperator != '(') 
      {
        q.enqueue(topOperator);
        s.pop(topOperator);
      }
      s.pop(topOperator); // Discard the '('
    } else 
    { // Operator
      char topOperator;
      while (s.peek(topOperator) == 0 && getPrecedence(topOperator) >= getPrecedence(current)) 
      {
        q.enqueue(topOperator);
        s.pop(topOperator);
      }
      s.push(current);
    }
    i++;
  }
}
Node* createExpTree(Queue& q)
{//create an expression tree from postfix expression
  char item;
  Node* treeStack[100];
  int top = -1;

  while (!q.isEmpty()) {
    q.dequeue(item);
    if (isalnum(item)) {
      Node* newNode = new Node;
      newNode->data = item;
      newNode->left = nullptr; 
      newNode->right = nullptr;
      treeStack[++top] = newNode;
    } else {
      if (top >= 1) {
        Node* rightOperand = treeStack[top--];
        Node* leftOperand = treeStack[top--];
        Node* newNode = new Node;
        newNode->data = item;
        newNode->right = rightOperand;
        newNode->left = leftOperand;
        treeStack[++top] = newNode;
      } else {
        cout << "Invalid postfix expression." << endl;
        return nullptr;
      }
    }
  }

  return treeStack[top];
}
void traverseInorder(Node* r)
{
  if (r!= nullptr) //if root is null , exit
  {
    traverseInorder(r->left);
    cout << r->data << " ";
    traverseInorder(r->right);
  }
}
void traversePreorder(Node* r)
{
  if (r != nullptr)
  {
    cout << r->data << " ";
    //recursively traverse left/right subtree
    traversePreorder(r->left);
    traversePreorder(r->right);
  }
}
void traversePostorder(Node* r)
{
  if (r != nullptr) 
  {
    traversePostorder(r->left);
    traversePostorder(r->right);
    cout << r->data << " ";
  }
}

