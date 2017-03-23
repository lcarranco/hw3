#include <cmath>
#include <cstdio>
#include <iostream>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <ostream>
#include <map>
#include <cassert>
#include "ArgumentManager.h"

using namespace std;

struct Node
{
    long long num = 0;
    string str;
    Node *prev = 0;
    Node *next = 0;
};
class DoubleLinkedList
{
  public:
    DoubleLinkedList() {}
    // Destructor
    ~DoubleLinkedList()
    {
        //cout << "DLL ~" << endl;
        clear();
    }

    void clear()
    {
        while (head != nullptr)
        {
            Node *deleteme = head;
            head = head->next;
            delete deleteme;
        }
    }

    // Copy constructor
    DoubleLinkedList(DoubleLinkedList const &list)
    {
        //cout << "DLL copy" << endl;
    }

    DoubleLinkedList &operator=(DoubleLinkedList const &other)
    {
        //cout << "DLL =" << endl;
        clear();

        Node *temp = other.head;
        while (temp != nullptr)
        {
            push_back(temp->str);
            temp = temp->next;
        }
        return *this;
    }

    void push_front(string parted)
    {
        Node *temp = new Node();
        temp->str = parted;
        stringstream ss(parted);
        ss >> temp->num;
        if (head == 0)
        {
            head = temp;
            tail = temp;
        }
        else
        {
            head->prev = temp;
            temp->next = head;
            head = temp;
        }
    }

    void push_back(string parted)
    {
        Node *temp = new Node();
        temp->str = parted;
        stringstream ss(parted);
        ss >> temp->num;
        if (head == 0)
        {
            head = temp;
            tail = temp;
        }
        else
        {
            tail->next = temp;
            temp->prev = tail;
            tail = temp;
        }
    }

    void print(ostream &out) const
    {
        Node *temp = head;
        while (temp != nullptr)
        {
            out << temp->str;
            temp = temp->next;
        }
    }

    Node at(int index) const
    {
        int i = 0;
        Node *temp = head;
        while (i != index)
        {
            temp = temp->next;
            i++;
        }
        return *temp;
    }

    int size() const
    {
        int count = 0;
        Node *temp = head;
        while (temp != 0)
        {
            temp = temp->next;
            count++;
        }
        return count;
    }

    void swap(DoubleLinkedList &other)
    {
        Node *temp = head;
        head = other.head;
        other.head = temp;
    }

  private:
    Node *head = 0;
    Node *tail = 0;
};


template <class Type>

class stackType

{
  private:
    int maxStackSize;
    int stackTop;
    Type *list;

  public:
    void initializeStack();
    bool isFullStack() const;
    bool isEmptyStack() const;
    void push(const Type &);
    void pop();
    Type top() const;
    stackType(int = 20);
    ~stackType();
};

template <class Type>

void stackType<Type>::initializeStack()
{
    stackTop = 0;
} //   end function initializeStack

template <class Type>

bool stackType<Type>::isFullStack() const
{
    return (stackTop == maxStackSize);
} //   end function isFullStack

//     check for stack empty
template <class Type>

bool stackType<Type>::isEmptyStack() const
{
    return (stackTop == 0);
} //   end function isEmptyStack

//     insert an element into stack

template <class Type>

void stackType<Type>::push(const Type &newItem)
{
    if (!isFullStack())
    {
        list[stackTop] = newItem;
        stackTop++;
    }
    else
        cout << "\n\tCan not add to a full stack";
}

//     delete an element from the stack

template <class Type>

void stackType<Type>::pop()
{
    if (!isEmptyStack())
        stackTop--;
    else
        cout << "\n\tCan not remove from an empty stack";
} //   end function pop

//     return the value of stack-top

template <class Type>

Type stackType<Type>::top() const
{
    assert(stackTop != 0);
    return list[stackTop - 1];

} //   end function top

//     constructor for the class stackType

template <class Type>

stackType<Type>::stackType(int stackSize)
{
    if (stackSize <= 0)
    {
        cout << "Invalid size";
        stackSize = 10;
    } //     end if
    else
        maxStackSize = stackSize;

    stackTop = 0;
    list = new Type[maxStackSize];

} //   end constructor stackType

//     destructor for the class stackType

template <class Type>

stackType<Type>::~stackType()
{
    delete[] list;
} //   end destructor stackType

class Bigex
{
  public:
    Bigex() {}
    ~Bigex()
    {
        //cout << "BN ~" << endl;
    }

    Bigex(string expression, int digitsPerNode)
    {
        //cout << num << endl;
        if (expression[0] == '-')
        {
            isNegative = true;
            expression.erase(expression.begin());
        }
        int startIndex = expression.length() - digitsPerNode;
        while (startIndex >= 0)
        {
            data.push_front(expression.substr(startIndex, digitsPerNode));
            startIndex -= digitsPerNode;
        }
        if (startIndex < 0)
        {
            data.push_front(expression.substr(0, startIndex + digitsPerNode));
        }
    }
    Bigex(Bigex const &other)
    {
        //cout << "BN copy" << endl;
        isNegative = other.isNegative;
        data = other.data;
    }
    Bigex &operator=(Bigex const &other)
    {
        //cout << "BN =" << endl;
        isNegative = other.isNegative;
        data = other.data;
        return *this;
    }

    void print(ostream &out) const
    {
        if (isNegative)
        {
            out << "-";
        }
        data.print(out);
    }

    void swap(Bigex &other)
    {
        std::swap(isNegative, other.isNegative);
        data.swap(other.data);
    }

  private:
    bool isNegative = false;
    DoubleLinkedList data;
};

class infixToPostfix
{
    string infix;
    string postfix;
    DoubleLinkedList data;
  public:
    void showPostfix();
    bool isOperator(const char c);
    int precedence(const char op1, const char op2);
    //void convert_sign();
    void getInfix(string infixString)
    {
        infix = infixString;
    }

    void showInfix()
    {
        cout << "\n\tInfix expression: " << infix;
    }
};

bool infixToPostfix::isOperator(const char c)
{

    if ((c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '('))
        return true;
    else
        return false;
}

int infixToPostfix::precedence(const char op1, const char op2)
{
    int pre1 = 0, pre2 = 0; //declare variables to compare the precedence

    if ((op1 == '^') || (op2 == '^'))
        cout << "Exponentiation was not considered for precedence. \n\tThe program may result in abnormal output of Postfix exp.";
    if ((op1 == '+') || (op1 == '-')) //low precedence
        pre1 = 0;
    else if ((op1 == '*') || (op1 == '/') || (op1 == '%'))
        pre1 = 1;                     //high precedence
    if ((op2 == '+') || (op2 == '-')) //low precedence
        pre2 = 0;
    else if ((op2 == '*') || (op2 == '/') || (op2 == '%'))
        pre2 = 1; //     high precedence

    //     compare and return the precedence of op1 & op2
    if (pre1 == pre2) //     equal precedence of op1 & op2
        return 0;
    else if (pre1 > pre2) //higher precedence of op1 over op2
        return 1;
    else //     lower precedence of op1 over op2
        return -1;
}

// void infixToPostfix::convert_sign()
// {
//     for(int i = 0; i < infix.length() - 1; i++)
//     {
//         if(infix[i] == '+' && infix[i + 1] == '+')
//         {
//             infix.erase(infix.begin() + i);
//         }
//         else if(infix[i] == '-' && infix[i + 1] == '-')
//         {
//             infix.erase(infix.begin() + i);
//             infix[i + 1] = '+';
//         }
//         else if(infix[i] == '+' && infix[i + 1] == '-')
//         {
//             infix.erase(infix.begin() + i);
//         }
//         else if(infix[i] == '-' && infix[i + 1] == '+')
//         {
//             infix.erase(infix.begin() + i + 1);
//         }
//     }
// }

//     conversion of infix arithmetic exp into postfix exp
void infixToPostfix::showPostfix()
{
    stackType<char> myStack; //A Stack of characters
    string pfx = "";
    infix.append(")"); //append a right parenthesis ')' to the end of infix
    myStack.push('('); //push the left parenthesis onto the stack
    unsigned int i = 0;
    do //loop through the infix array
    {
        if((isOperator(infix[i]) && (isOperator(infix[i+1])) == '-'))
          {
            infix[i+1] = '~';
            }
        else if((isOperator(infix[i]) && (isOperator(infix[i+1])) == '+'))
          {
            //infix.erase(infix.begin() + i + 1);
            infix[i+1] = ' ';
          }
        else if (isOperator(infix[i])) //If the operator is an element in the string
        {
            if (!myStack.isEmptyStack() && isOperator(myStack.top())) //when the top of the stack is an operator
            {
                if (precedence(infix[i], myStack.top()) == 0) //find the precedence of the operator
                {
                    pfx = pfx + myStack.top(); //place the operator in postfix
                    myStack.pop(); //Pop the stack
                    pfx += ' ';
                }
                else if (precedence(infix[i], myStack.top()) == 1)
                {
                    myStack.push(infix[i]); //push into stack the infix elem when higher precedence
                    pfx += ' ';
                    i++;
                }
                else
                {
                    pfx = pfx + myStack.top(); //place the element in postfix & pop the stack
                    myStack.pop();
                    pfx += ' '; // add whitespace for each operation on the stack.
                }
            }
            else
            {
                myStack.push(infix[i]); //push onto stack when top of stack  is not an operator
                pfx += ' ';
                i++;
            }
        }
        else if (infix[i] == ')')
        {
            while (!myStack.isEmptyStack() && myStack.top() != '(') //get the elements from the stack
            {
                pfx = pfx + myStack.top();

                myStack.pop();
            }
            myStack.pop(); //pop the '(' from the stack
            i++;
        }
        else if (infix[i] == '(')
        {
            myStack.push(infix[i]); //neither operator nor operand push onto stack
            if(infix[i+1] == '~') {
                pfx+= '~';

            }
            else if(infix[i+1] == '+') {
              infix.erase(infix.begin() + i + 1);
            }
            pfx += ' ';
            i++;
        } //end if
        else
        {
            pfx = pfx + infix[i]; //In case of operands, copy the operands  from infix to postfix
            i++;
        }
    } while (i < infix.length());
    cout << "\n\tPostfix Expression: " << pfx;
}


// void print(Bigex *a, int size, ostream & out)
// {
//     a[0].print(out);
//     for (int i = 1; i < size; i++)
//     {
//         out << endl;
//         a[i].print(out);
//     }
// }

int count_lines(string &filename, int digitsPerNode)
{
    std::ifstream ifs(filename.c_str());

    int counter = 0;
    while (!ifs.eof())
    {
        string line;
        ifs >> line;
        counter++;
    }

    return counter;
}

int main(int argc, char *argv[])
{
    // if (argc < 2)
    // {
    //     //std::cerr("Usage: infinitearithmetic \"input=xyz.txt;digitsPerNode=<number>\"\n");
    //     return 1;
    // }
    // ArgumentManager am(argc, argv);
    // std::string filename = am.get("input");
    // int digitsPerNode = std::stoi(am.get("digitsPerNode"));
    // int size = count_lines(filename, digitsPerNode);

    infixToPostfix InfixExp;
    string infix;

    ifstream infile;
    infile.open("7.txt", ios::in);
    if (!infile)
    {
        cout << "Cannot open input file. Program terminates!!!" << endl;
        return 1;
    }
    getline(infile, infix); //reading first line
    while (infile)
    {
        InfixExp.getInfix(infix);
        InfixExp.showInfix();
        //InfixExp.convert_sign();
        InfixExp.showPostfix();
        cout << endl;
        getline(infile, infix); //reading next line
    }
    infile.close();
    return 0;
}
