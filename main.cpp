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
  int pop(char& item);
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

//fxn prototypes
bool isOp(char c); //check if char is operator
int getPrecedence(char c);//get an operators precedence
void InfixtoPostfix(const char* in, char* post);//convert infix expression to postfix
Node* createExpTree(const char* post);
void traverseInorder(Node* r); //travers tree inorder, passes in the root ptr
void traversePreorder(Node* r);
void traversePostorder(Node* r);



int main()
{//prompts, drver code
  char infix[100];
  char postfix[100];
  cout << "Enter infix expresion: ";
  cin.getline(infix, 100);

  InfixtoPostfix(infix, postfix);
  cout << "Postfix expression: " << postfix << endl;

  Node* root = createExpTree(postfix);
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
int Stack::pop(char& item)
{
  if(isEmpty())
  {
    return -1;
    
    item = arr[top--];
    return 0;
  }
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

int Stack::print()
{
  if(isEmpty())
    {
      cout << "empty stack" << endl;
      return -1;
    }
  for(int x = top; x >= 0; x--)
    {
      cout << arr[x] << " " << endl;
    }
  return 0;
}

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
  if(front > rear)
    {
      front = rear = -1;
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
  return c == '+' || c == '-'|| c== '*'|| c == '/'|| c =='^';

}
int getPrecedence(char c)
{
  if (c == '^')
  {
    return 3;
  }
  else if (c == '*' || c == '/')
  {
    return 2;
  }else if (c == '+' || c == '-')
  {
    return 1;
  }else
  {
    return -1;
      }
}
void InfixtoPostfix(const char* in, char* post)
{//convert infix expression to postfix expr.
  Stack operatorStack;
  int postfixIndex = 0;
  for (int z = 0; z < strlen(in); z++) 
  {
    if (in[z] == ' ')
     {
      continue;
     } 
    if (isalnum(in[z])) 
    {
      post[postfixIndex++] = in[z];
    } else if (in[z] == '(') 
    {
      operatorStack.push(in[z]);
    } else if (in[z] == ')') 
    {
      char topOperator;
      while (!operatorStack.isEmpty() && (operatorStack.peek(topOperator) != -1) && topOperator != '(') 
      {//otherwise it would keep going
        operatorStack.pop(topOperator);
        post[postfixIndex++] = topOperator;
      }
      operatorStack.pop(topOperator); // Pop '('
    } else 
    {
      char topOperator;
      while (!operatorStack.isEmpty() && (operatorStack.peek(topOperator) != -1) 
              && topOperator != '(' 
              && getPrecedence(topOperator) >= getPrecedence(in[z])) 
      {
        operatorStack.pop(topOperator);
        post[postfixIndex++] = topOperator;
      }
      operatorStack.push(in[z]);
    }
    }

    while (!operatorStack.isEmpty()) 
    {
      char topOperator;
      operatorStack.pop(topOperator);
      post[postfixIndex++] = topOperator;
    }

    post[postfixIndex] = '\0';
}
Node* createExpTree(const char* post)
{//create an expression tree from postfix expression
  Stack treeStack;
  for (int a = 0; a < strlen(post); a++) 
  {
    if (isalnum(post[a])) 
    {
      Node* newNode = new Node;
      newNode->data = post[a];
      newNode->left = newNode->right = nullptr;
      treeStack.push(post[a]);
    } 
    else 
    {
      char pChar;
      treeStack.pop(pChar); // Pop operator
      Node* newNode = new Node;
      newNode->data = post[a];
      newNode->right = reinterpret_cast<Node*>(treeStack.pop(pChar)); // Pop right operand
      newNode->left = reinterpret_cast<Node*>(treeStack.pop(pChar)); // Pop left operand
      treeStack.push(reinterpret_cast<char&>(*newNode)); // Push the new node
    }
  }
  return reinterpret_cast<Node*>(treeStack.pop()); // Pop and return the root node converting ptr type bc stack is char*
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

