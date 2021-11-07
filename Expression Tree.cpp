//Hiva Mohammadzadeh [Thursday Night]
//Lab 7 (Binary Trees)

#include<iostream>
#include<fstream>
#include<string>

using namespace std;

#define SIZE 35

typedef struct Node {
    
    char info;
    Node *left;
    Node *right;
    void push(Node*);
    Node* pop();
    
} *ptrNode;

ptrNode myStack[SIZE];
int top = -1;

ptrNode createNode(char b) {
    
    ptrNode temp;
    temp = new Node();
    temp->info = b;
    temp->left = nullptr;
    temp->right = nullptr;
    return(temp);
    
}

void Node::push(ptrNode temp) {
    
    myStack[++top] = temp;
    
}

ptrNode Node::pop() {
    
    ptrNode p;
    p = myStack[top--];
    return(p);
    
}

///

class Stack {
    
private:
    
    struct st_Node {
        public:
        
            st_Node * next;
            char entry;
        };
    
    st_Node *ptrHead;
    
public:
    
    Stack();
    ~Stack();
    void pushStack(char info);
    void pop();
    bool isEmpty();
    char& top();
    const char& topStack();
};

Stack::Stack() {
    ptrHead = nullptr;
}


bool Stack::isEmpty() {
    return ptrHead == nullptr ? true : false;
}

char& Stack::top() {
    return ptrHead->entry;
}

const char& Stack::topStack() {
    return ptrHead->entry;
}

Stack::~Stack() {
    while (ptrHead != nullptr) {
        st_Node *temp = ptrHead;
        ptrHead = ptrHead->next;
        delete temp;
    }
}

void Stack::pushStack(char info) {
    
    st_Node *new_Node = new (nothrow) st_Node;

    if (new_Node == nullptr) {
        
        cout << "Memory could not be allocated. Exiting the program...\n";
        system("pause");
        exit(1);
    }

    new_Node->entry = info;
    new_Node->next = nullptr;
    
    if (isEmpty()) {
        
        ptrHead = new_Node;
    }
    else {
        
        new_Node->next = ptrHead;
        ptrHead = new_Node;
    }
}

void Stack::pop() {
    
    char info;
    
    if (isEmpty()) {
        
        cout << "Cannot delete from empty stack.\n";
    }
    else {
        
        st_Node *temp = ptrHead;
        ptrHead = ptrHead->next;
        info = temp->entry;
        delete temp;
    }
}

///

class Tree {
    
public:
    
    void doPrefix(Node*);
    void doInfix(Node*);
    void doPostfix(Node*);
};

void Tree::doPrefix(ptrNode tree) {
    
    if (tree != nullptr) {
        
        cout << tree->info << " ";
        doPrefix(tree->left);
        doPrefix(tree->right);
    }
}

void Tree::doInfix(ptrNode tree) {
    
    if (tree != nullptr) {
        
        cout << "(";
        doInfix(tree->left);
        cout << tree->info;
        doInfix(tree->right);
        cout << ")";
        
    }
}

void Tree::doPostfix(ptrNode tree) {
    
    if (tree != nullptr) {
        
        doPostfix(tree->left);
        doPostfix(tree->right);
        cout << tree->info << " ";
    }
}

///


string inToPost(string s);
ptrNode createNode(char b);
void printMenu();
int precedence(char ch);


int main() {
    
    ifstream fp;
    Tree tree;
    Node node;
    string expression;
    ptrNode temp = nullptr;

    int choice = 0;

    fp.open("/Users/hivamoh/Desktop/CS 136/Labs/CS 136 Lab 7 FINALL/136lab7file.txt");
    
    if (!fp.is_open()) {
        
        cout << "\nInput file could not be opened\n.";
    }

    while (!fp.eof()) {
        
        getline(fp, expression);
       
        
        cout << "\nThe expression from the file:  " << expression<< endl;
        
        expression = inToPost(expression);

        for (int i = 0; expression[i] != 0; i++) {

            if (expression[i] == '*' || expression[i] == '/' || expression[i] == '+' || expression[i] == '-') {
                
                temp = createNode(expression[i]);
                temp->right = node.pop();
                temp->left = node.pop();
                node.push(temp);
            }
            else {
                
                temp = createNode(expression[i]);
                node.push(temp);
            }
        }

        do {
            
            printMenu();
            cin >> choice;
            
            switch (choice) {
                    
            case 1:
                    
                cout << "\nPreorder Expression:\t";
                tree.doPrefix(temp);
                cout << endl;
                break;
                    
            case 2:
                    
                cout << "\nInorder Expression:\t";
                tree.doInfix(temp);
                cout << endl;
                break;
                    
            case 3:
                    
                cout << "\nPostorder Expression:\t";
                tree.doPostfix(temp);
                cout << endl;
                break;
                    
            case 4:
                if (!fp.eof()) {
                    
                    cout << "\nLoading the next expression...\n" << endl;
                                   
                }
                else
                    cout << "\nNo more expressions in file.\n\nQuitting the Program\n" << endl;
                
                break;
                    
            case 5:
                    
                cout << "\nQuitting the program...\n";
                system("pause");
                exit(1);
                break;
                    
            default:
                    
                cout << "\nPlease enter a valid menu choice.\n";
                cin.clear();
                cin.ignore(200, '\n');
                break;
                    
            }
            
        } while (choice != 4);
    }
    
    fp.close();
    return 0;
}

void printMenu() {
    
    cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n"
         << "How would you like to display your expression?\n\n"
         << "1: preorder\n"
         << "2: inorder\n"
         << "3: postorder\n"
         << "4: load next expression from file\n"
         << "5: quit\n"
         << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n"
         << "\nEnter your choice of 1 - 5: "<< endl;
}

string inToPost(string myStr) {
    
    Stack st;
    st.pushStack('N');
    
    string info;

    for (int i = 0; i < myStr.length(); i++) {
        
        if (isalnum(myStr[i])) {
            
            info += myStr[i];
        }

        else if (myStr[i] == '(') {
            
            st.pushStack('(');
        }

        else if (myStr[i] == ')') {
            
            while (st.top() != 'N' && st.top() != '(') {
                
                char ch = st.top();
                st.pop();
                info += ch;
            }
            
            if (st.top() == '(') {
                
                st.pop();
            }
        }
        
        else {
            
            while (st.top() != 'N' && precedence(myStr[i]) <= precedence(st.top())) {
                
                char ch = st.topStack();
                st.pop();
                info += ch;
            }
            
            st.pushStack(myStr[i]);
        }
    }

    while (st.topStack() != 'N') {
        
        char ch = st.topStack();
        st.pop();
        info += ch;
    }
    return info;
}



int precedence(char ch) {
    
    if (ch == '-' || ch == '+') {
        
        return 1;
    }
    
    else if (ch == '*' || ch == '/') {
        
        return 2;
    }
    
    return 0;
}

/*
 INPUT FILE:
 1*4/5
 6+1/2
 B*e
 x+y*a/b
 y*z+a/c
 r+t*qe/r
 abcde+/-*
 por/+e*t-*u
 c*j+k/d+z+g+n+f
 */
/*

 
 The expression from the file:  1*4/5

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 How would you like to display your expression?

 1: preorder
 2: inorder
 3: postorder
 4: load next expression from file
 5: quit
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 Enter your choice of 1 - 5:
 fdhfagsdbhj

 Please enter a valid menu choice.

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 How would you like to display your expression?

 1: preorder
 2: inorder
 3: postorder
 4: load next expression from file
 5: quit
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 Enter your choice of 1 - 5:
 78127

 Please enter a valid menu choice.

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 How would you like to display your expression?

 1: preorder
 2: inorder
 3: postorder
 4: load next expression from file
 5: quit
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 Enter your choice of 1 - 5:
 1

 Preorder Expression:    / * 1 4 5

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 How would you like to display your expression?

 1: preorder
 2: inorder
 3: postorder
 4: load next expression from file
 5: quit
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 Enter your choice of 1 - 5:
 2

 Inorder Expression:    (((1)*(4))/(5))

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 How would you like to display your expression?

 1: preorder
 2: inorder
 3: postorder
 4: load next expression from file
 5: quit
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 Enter your choice of 1 - 5:
 3

 Postorder Expression:    1 4 * 5 /

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 How would you like to display your expression?

 1: preorder
 2: inorder
 3: postorder
 4: load next expression from file
 5: quit
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 Enter your choice of 1 - 5:
 4

 Loading the next expression...


 The expression from the file:  6+1/2

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 How would you like to display your expression?

 1: preorder
 2: inorder
 3: postorder
 4: load next expression from file
 5: quit
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 Enter your choice of 1 - 5:
 1

 Preorder Expression:    + 6 / 1 2

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 How would you like to display your expression?

 1: preorder
 2: inorder
 3: postorder
 4: load next expression from file
 5: quit
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 Enter your choice of 1 - 5:
 2

 Inorder Expression:    ((6)+((1)/(2)))

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 How would you like to display your expression?

 1: preorder
 2: inorder
 3: postorder
 4: load next expression from file
 5: quit
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 Enter your choice of 1 - 5:
 3

 Postorder Expression:    6 1 2 / +

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 How would you like to display your expression?

 1: preorder
 2: inorder
 3: postorder
 4: load next expression from file
 5: quit
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 Enter your choice of 1 - 5:
 4

 Loading the next expression...


 The expression from the file:  B*e

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 How would you like to display your expression?

 1: preorder
 2: inorder
 3: postorder
 4: load next expression from file
 5: quit
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 Enter your choice of 1 - 5:
 1

 Preorder Expression:    * B e

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 How would you like to display your expression?

 1: preorder
 2: inorder
 3: postorder
 4: load next expression from file
 5: quit
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 Enter your choice of 1 - 5:
 2

 Inorder Expression:    ((B)*(e))

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 How would you like to display your expression?

 1: preorder
 2: inorder
 3: postorder
 4: load next expression from file
 5: quit
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 Enter your choice of 1 - 5:
 3

 Postorder Expression:    B e *

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 How would you like to display your expression?

 1: preorder
 2: inorder
 3: postorder
 4: load next expression from file
 5: quit
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 Enter your choice of 1 - 5:
 4

 Loading the next expression...


 The expression from the file:  x+y*a/b

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 How would you like to display your expression?

 1: preorder
 2: inorder
 3: postorder
 4: load next expression from file
 5: quit
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 Enter your choice of 1 - 5:
 1

 Preorder Expression:    + x / * y a b

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 How would you like to display your expression?

 1: preorder
 2: inorder
 3: postorder
 4: load next expression from file
 5: quit
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 Enter your choice of 1 - 5:
 2

 Inorder Expression:    ((x)+(((y)*(a))/(b)))

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 How would you like to display your expression?

 1: preorder
 2: inorder
 3: postorder
 4: load next expression from file
 5: quit
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 Enter your choice of 1 - 5:
 3

 Postorder Expression:    x y a * b / +

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 How would you like to display your expression?

 1: preorder
 2: inorder
 3: postorder
 4: load next expression from file
 5: quit
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 Enter your choice of 1 - 5:
 4

 Loading the next expression...


 The expression from the file:  y*z+a/c

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 How would you like to display your expression?

 1: preorder
 2: inorder
 3: postorder
 4: load next expression from file
 5: quit
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 Enter your choice of 1 - 5:
 1

 Preorder Expression:    + * y z / a c

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 How would you like to display your expression?

 1: preorder
 2: inorder
 3: postorder
 4: load next expression from file
 5: quit
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 Enter your choice of 1 - 5:
 2

 Inorder Expression:    (((y)*(z))+((a)/(c)))

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 How would you like to display your expression?

 1: preorder
 2: inorder
 3: postorder
 4: load next expression from file
 5: quit
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 Enter your choice of 1 - 5:
 3

 Postorder Expression:    y z * a c / +

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 How would you like to display your expression?

 1: preorder
 2: inorder
 3: postorder
 4: load next expression from file
 5: quit
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 Enter your choice of 1 - 5:
 4

 Loading the next expression...


 The expression from the file:  r+t*qe/r

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 How would you like to display your expression?

 1: preorder
 2: inorder
 3: postorder
 4: load next expression from file
 5: quit
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 Enter your choice of 1 - 5:
 1

 Preorder Expression:    + t / * q e r

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 How would you like to display your expression?

 1: preorder
 2: inorder
 3: postorder
 4: load next expression from file
 5: quit
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 Enter your choice of 1 - 5:
 2

 Inorder Expression:    ((t)+(((q)*(e))/(r)))

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 How would you like to display your expression?

 1: preorder
 2: inorder
 3: postorder
 4: load next expression from file
 5: quit
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 Enter your choice of 1 - 5:
 3

 Postorder Expression:    t q e * r / +

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 How would you like to display your expression?

 1: preorder
 2: inorder
 3: postorder
 4: load next expression from file
 5: quit
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 Enter your choice of 1 - 5:
 4

 Loading the next expression...


 The expression from the file:  abcde+/-*

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 How would you like to display your expression?

 1: preorder
 2: inorder
 3: postorder
 4: load next expression from file
 5: quit
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 Enter your choice of 1 - 5:
 1

 Preorder Expression:    - a * b + c / d e

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 How would you like to display your expression?

 1: preorder
 2: inorder
 3: postorder
 4: load next expression from file
 5: quit
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 Enter your choice of 1 - 5:
 2

 Inorder Expression:    ((a)-((b)*((c)+((d)/(e)))))

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 How would you like to display your expression?

 1: preorder
 2: inorder
 3: postorder
 4: load next expression from file
 5: quit
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 Enter your choice of 1 - 5:
 3

 Postorder Expression:    a b c d e / + * -

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 How would you like to display your expression?

 1: preorder
 2: inorder
 3: postorder
 4: load next expression from file
 5: quit
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 Enter your choice of 1 - 5:
 4

 Loading the next expression...


 The expression from the file:  por/+e*t-*u

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 How would you like to display your expression?

 1: preorder
 2: inorder
 3: postorder
 4: load next expression from file
 5: quit
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 Enter your choice of 1 - 5:
 1

 Preorder Expression:    - p * + / o r * e t u

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 How would you like to display your expression?

 1: preorder
 2: inorder
 3: postorder
 4: load next expression from file
 5: quit
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 Enter your choice of 1 - 5:
 2

 Inorder Expression:    ((p)-((((o)/(r))+((e)*(t)))*(u)))

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 How would you like to display your expression?

 1: preorder
 2: inorder
 3: postorder
 4: load next expression from file
 5: quit
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 Enter your choice of 1 - 5:
 3

 Postorder Expression:    p o r / e t * + u * -

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 How would you like to display your expression?

 1: preorder
 2: inorder
 3: postorder
 4: load next expression from file
 5: quit
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 Enter your choice of 1 - 5:
 4

 Loading the next expression...


 The expression from the file:  c*j+k/d+z+g+n+f

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 How would you like to display your expression?

 1: preorder
 2: inorder
 3: postorder
 4: load next expression from file
 5: quit
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 Enter your choice of 1 - 5:
 1

 Preorder Expression:    + + + + + * c j / k d z g n f

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 How would you like to display your expression?

 1: preorder
 2: inorder
 3: postorder
 4: load next expression from file
 5: quit
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 Enter your choice of 1 - 5:
 2

 Inorder Expression:    (((((((c)*(j))+((k)/(d)))+(z))+(g))+(n))+(f))

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 How would you like to display your expression?

 1: preorder
 2: inorder
 3: postorder
 4: load next expression from file
 5: quit
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 Enter your choice of 1 - 5:
 3

 Postorder Expression:    c j * k d / + z + g + n + f +

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 How would you like to display your expression?

 1: preorder
 2: inorder
 3: postorder
 4: load next expression from file
 5: quit
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 Enter your choice of 1 - 5:
 4

 No more expressions in file.

 Quitting the Program

 Program ended with exit code: 0
 */
