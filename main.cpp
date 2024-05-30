#include <iostream>
#include <cstring>
#include <cctype>

/*
ghazi abbas
c++/ds DC galbraith
spring sem

binary expression tree
v2

Sources:
old project that did not work 
+
prof. Fant lectures on mr galbraiths canvas page
+
https://www.youtube.com/watch?v=_LxbhLNRZkI
https://www.youtube.com/watch?v=BHB0B1jFKQc
https://www.youtube.com/watch?v=om1C190DfPc
https://www.youtube.com/watch?v=WLvU5EQVZqY 


*/
using namespace std;


class Node
{//rewrote node class to combine for each
 public:
  Node* left;
  Node* right;
  Node* next;
  Node* treeNode;
  char data;

    Node(Node* left, Node* right, Node* next, char data) 
    {
      this->left = left;
      this->right = right;
      this->next = next;
      this->data = data;
    }

    //char constructor
    Node(char data) 
    {
      this->data = data;
      left = NULL;
      right = NULL;
      next = NULL;
    }

    //separate constructor for treenode
    Node(Node* treeNode) 
    {
      this->treeNode = treeNode;
      left = NULL;
      right = NULL;
      next = NULL;
      data = '\0';
    }

    //n constructor
    Node(Node* left, Node* right, char data) 
    {
      this->left = left;
      this->right = right;
      this->treeNode = NULL;
      this->data = data;
      next = NULL;
    }

    //default constructor
    Node() 
    {
        left = NULL;
        right = NULL;
        next = NULL;
        data = ' ';
    }
};

//redone as a struct
struct Stack 
{
 
    Node* head = nullptr;
    
    //stack functions required and stuff
    void push(char c) 
    {
        Node* newNode = new Node(c);
        if (head == NULL) 
        {
            head = newNode;
            return;
        }
        newNode->next = head;
        head = newNode;
    }

    void pop() 
    {
        if (head == NULL) 
        {
            return;
        }

        Node* temp;
        temp = head;
        head = head->next;
        delete temp;
    }
    
    char peek()
    {
        if (head == NULL) 
        {
            return '\0';
        }
        return head->data;
    }

    void print() 
    {
        Node* c = head;
        while (c != NULL) 
        {
            cout << c->data;
            c = c->next;
        }
        cout << endl;
    }

};

//separate tree stack
struct TreeStack 
{

  Node* head = NULL;
  void push(Node * n) 
  {
    Node* newNode = new Node(n);
    if (head == NULL) 
    {
      head = newNode;
      return;
    }
    newNode->next = head;
    head = newNode;
  }

  //remove top
  void pop() 
  {
    if (head == NULL) 
    {
      return;
    }
    Node * temp;
    temp = head;
    head = head->next;
    delete temp;
  }

  //get th e head
  Node* peek() 
  {
    if (head == NULL) 
    {
      return NULL;
    }
    return head->treeNode;
  }

};

//q implemented as a struct
struct Queue {

  Node* head = NULL;
  Node* tail = NULL;

  void enqueue(char c) 
  {
    Node * newNode = new Node(c);
    if (head == NULL) 
    {
      head = newNode;
      tail = head;
      return;
    }
    tail->next = newNode;
    tail = newNode;
  }

  //removing  head of the queue get symbol
  void dequeue() 
  {
    if (head == NULL) 
    {
      return;
    }
    Node * temp;
    temp = head;
    head = head->next;
    delete temp;
  }

  //get head 
  char peek() 
  {
    if (head == NULL) 
    {
      return '\0';
    }
    return head->data;
  }

  //print fcxn
  void print() 
  {
    Node* c = head;
    while (c != NULL) 
    {
      cout << c->data;
      c = c->next;
    }
    cout << endl;
  }
};
//fxn prototypes
Node* createExpTree(Queue);
void printExpTree(Node*, int);
void infix(Node*);
void pefix(Node*);
void postfix(Node*);
int checkPrecedence(char c);

Node* createExpTree(Queue out)
{
    char data = out.peek();
    TreeStack treeStack; //stack holds tree nodes
    while (data != '\0') //until end of que 
    {
        if (isdigit(data)) 
        {//operand
            Node* treeNode = new Node(data);
            treeStack.push(treeNode);
        }
        else 
        {
            //isOp
            Node* rightChild = treeStack.peek();
            treeStack.pop();
            Node* leftChild = treeStack.peek();
            treeStack.pop();
            Node* operatorNode = new Node(leftChild, rightChild, data);
            treeStack.push(operatorNode);
        }
        out.dequeue();
        data = out.peek();
    }
    //first in is root
    Node* root = treeStack.peek();
    return root;
}
void printExpTree(Node* c, int h)
{

  if (c== NULL) 
  {
    return;
  }

  printExpTree(c->right, h + 1);

  for (int i = 0; i < h; i++) 
  {
    cout <<"\t";
  }
  cout << c->data << endl;

  printExpTree(c->left, h + 1);
  
}
//couldve just copied these from v1
void infix(Node* c)
{

  if (c == NULL) 
  {
    return;
  }

  infix(c->left);

  cout << c->data;

  infix(c->right);
}
void prefix(Node* c)
{
    if (c == NULL) 
    {
        return;
    }
    cout << c->data;
    //traverse each
    prefix(c->left);
    prefix(c->right);
}
void postfix(Node* c)
{

  if (c == NULL) 
  {
    return;
  }

  postfix(c->left);
  postfix(c->right);

  cout << c->data;

}

int checkPrecedence(char c) 
{//also from v1

  if (c == '+' || c == '-') 
  {
    return 1;
  }
  else if (c == '*' || c == '/') 
  {
    return 2;
  }
  else if (c == '^') 
  {
    return 3;
  }
  else if (c == '(' || c == ')') 
  {
    return 4;
  }
  else 
  {//error handling?!!?
    return 0;
  }
}

int main() 
{

  char* expression = new char[30];
  char* input = new char[20];
  Stack s;
  Queue q;
  
  cout << "\n Enter expression: ";
  cin.get(expression, 30);
  cin.get();

  for (int x = 0; x < strlen(expression); x++) 
  {
    if (expression[x] == ' ') 
    {
        //space
    }
    else if (isdigit(expression[x]) == 1) 
    {
      //intgoes to queue
      q.enqueue(expression[x]);
    }
    else 
    {
        //get current character
      char input = expression[x];
      int ip = checkPrecedence(input);
      if (input == '(') 
      {
	    //opening parenthesis
	    s.push(input);
      }
      else if (input == ')') 
      {
	    //closing parenthes
        char top = s.peek();
        while (top != '\0' && top != '(') 
        {
            //pop the top element from the stack and enqueue it
            s.pop();
            q.enqueue(top);
            top = s.peek();
        }
        if (top == '(') 
        {
            s.pop();
        }
      }
      else 
      {
        char top = s.peek();
        int tp = checkPrecedence(top);
        //other
        while (top != '\0' && top != '(' && (tp > ip || (tp == ip && input != '^'))) 
        {
            s.pop();
            q.enqueue(top);
            top = s.peek();
            tp = checkPrecedence(top);
        }
        s.push(input);
      }
    }
  }

  //add stack until empty
  while (s.peek() != '\0') 
  {
    q.enqueue(s.peek());
    s.pop();
  }

  //print queue contents as is
  s.print();

  Node * root = createExpTree(q);
  cout << endl;
  //print tree
  cout << "tree:" << endl;
  printExpTree(root, 0);

    cout << "infix: ";
    infix(root);
    cout << endl;
    cout << "prefix: ";
    prefix(root);
    cout << endl;
    cout << "postfix: ";
    postfix(root);
    cout << endl;  
  return 0;
  
}
