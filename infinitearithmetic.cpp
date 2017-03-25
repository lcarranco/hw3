#include "stdafx.h"

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
        while(head != nullptr)
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
        while(temp != nullptr)
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
        if(head == 0)
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
        if(head == 0)
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
        while(temp != nullptr)
        {
            out << temp->str;
            temp = temp->next;
        }
    }

    Node at(int index) const
    {
        int i = 0;
        Node *temp = head;
        while(i != index)
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
        while(temp != 0)
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
    if(!isFullStack())
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
    if(!isEmptyStack())
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
    if(stackSize <= 0)
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

    Bigex(int digitsPerNode)
        : digitsPerNode(digitsPerNode)
    {}

    Bigex(string expression, int digitsPerNode)
        : digitsPerNode(digitsPerNode)
    {
        if(expression[0] == '-')
        {
            isNegative = true;
            expression.erase(expression.begin());
        }
        int startIndex = expression.size() - digitsPerNode;
        // BUG: an extra empty node is being added
        // FIX: swap the = for next two statements
        while(startIndex > 0)
        {
            data.push_front(expression.substr(startIndex, digitsPerNode));
            startIndex -= digitsPerNode;
        }
        if(startIndex <= 0)
        {
            data.push_front(expression.substr(0, startIndex + digitsPerNode));
        }
    }
    Bigex(Bigex const &other)
    {
        //cout << "BN copy" << endl;
        isNegative = other.isNegative;
        data = other.data;
        digitsPerNode = other.digitsPerNode;
    }
    Bigex &operator=(Bigex const &other)
    {
        //cout << "BN =" << endl;
        isNegative = other.isNegative;
        data = other.data;
        digitsPerNode = other.digitsPerNode;
        return *this;
    }

    // Makes copies of Bigex objects, so that they don't change.
    Bigex operator+(Bigex &other)
    {
        return add(Bigex(*this), Bigex(other));
    }
    Bigex operator-(Bigex &other)
    {
        return sub(Bigex(*this), Bigex(other));
    }

    Bigex operator*(Bigex const &other)
    {
        Bigex const & bigexA = *this;
        Bigex const & bigexB = other;
        Bigex result(digitsPerNode);

        int indexA = bigexA.data.size() - 1;
        long long count = 0;
        while(indexA > -1)
        {
            Bigex tempresult(digitsPerNode);
            for(int i = 0; i < count; i++)
            {
                tempresult.data.push_front("000");
            }
            count++;
            int indexB = bigexB.data.size() - 1;
            int rollover = 0;
            while(indexB > -1)
            {
                long long num = (bigexA.data.at(indexA).num * bigexB.data.at(indexB).num) + rollover;
                indexB--;
                rollover = num / pow(10, digitsPerNode);
                num = num % (int)pow(10, digitsPerNode);
                string str = numtostring(num);
                if(rollover > 0 || indexB > -1)
                {
                    padzeros(str);
                }
                tempresult.data.push_front(str);
            }
            if(rollover > 0)
            {
                string str = numtostring(rollover);
                tempresult.data.push_front(str);
            }
            result = add(result, tempresult);
            indexA--;
        }

        if(bigexA.isNegative || bigexB.isNegative)
        {
            result.isNegative = true;
        }
        if(bigexA.isNegative && bigexB.isNegative)
        {
            result.isNegative = false;
        }
        return result;
    }

    void print(ostream &out) const
    {
        if(isNegative)
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
    Bigex add(Bigex bigexA, Bigex bigexB)
    {
        Bigex result(digitsPerNode);

        // Sign Manipulation
        if(!bigexA.isNegative && bigexB.isNegative)
        {
            // A + -B => A - B
            bigexA.isNegative = false;
            bigexB.isNegative = false;
            return sub(bigexA, bigexB);
        }
        if(bigexA.isNegative && !bigexB.isNegative)
        {
            // -A + B => B - A
            return sub(bigexB, bigexA);
        }
        if(bigexA.isNegative && bigexB.isNegative)
        {
            // -A + -B => -(A + B)
            result.isNegative = true;
        }

        int rollover = 0;
        int indexA = bigexA.data.size() - 1;
        int indexB = bigexB.data.size() - 1;

        // add all nodes together
        while(indexA > -1 || indexB > -1)
        {
            int a = 0;
            int b = 0;

            if(indexA > -1)
            {
                a = bigexA.data.at(indexA).num;
                indexA--;
            }
            if(indexB > -1)
            {
                b = bigexB.data.at(indexB).num;
                indexB--;
            }

            long long num = a + b + rollover;
            rollover = num / pow(10, digitsPerNode);
            num = num % (int)pow(10, digitsPerNode);

            string str;
            stringstream ss;
            ss << num;
            ss >> str;
            // this says if we aren't on the last node, pad the string
            if(rollover > 0 || indexA > -1 || indexB > -1)
            {
                padzeros(str);
            }
            result.data.push_front(str);
        }
        // add a node for the carry if necessary
        if(rollover > 0)
        {
            string str;
            stringstream ss;
            ss << rollover;
            ss >> str;
            result.data.push_front(str);
        }
        return result;
    }
    Bigex sub(Bigex bigexA, Bigex bigexB)
    {
        // Sign Manipulation
        if(!bigexA.isNegative && bigexB.isNegative)
        {
            // A - -B => A + B
            bigexA.isNegative = false;
            bigexB.isNegative = false;
            return add(bigexA, bigexB);
        }
        if(bigexA.isNegative && !bigexB.isNegative)
        {
            // -A - B => -A + -B
            bigexA.isNegative = true;
            bigexB.isNegative = true;
            return add(bigexA, bigexB);
        }
        if(bigexA.isNegative && bigexB.isNegative)
        {
            // -A - -B => -A + B => B - A
            bigexA.isNegative = false;
            bigexB.isNegative = false;
            return sub(bigexB, bigexA);
        }

        // algorithm
        // find larger number
        Bigex bigexL;
        Bigex bigexS;
        Bigex bigex9;

        int nodesA = bigexA.data.size() - 1;
        int nodesB = bigexB.data.size() - 1;
        int charsA = bigexA.data.at(0).str.size();
        int charsB = bigexB.data.at(0).str.size();
        int const EQUAL = 0;
        int const BIG_A = 1;
        int const BIG_B = 2;
        int which = EQUAL;
        if(nodesA > nodesB)
        {
            which = BIG_A;
        }
        if(nodesA < nodesB)
        {
            which = BIG_B;
        }
        if(nodesA == nodesB)
        {
            if(charsA > charsB)
            {
                which = BIG_A;
            }
            else
            {
                which = BIG_B;
            }
        }

        int nodes = 0;
        int chars = 0;
        if(which == BIG_A)
        {
            // use bigexA
            bigexL = bigexA;
            bigexS = bigexB;
            nodes = (bigexA.data.size() - 1);
            chars = bigexA.data.at(0).str.size();
            bigex9.digitsPerNode = bigexA.digitsPerNode;
        }
        else
        {
            // use bigexB
            bigexL = bigexB;
            bigexS = bigexA;
            nodes = (bigexB.data.size() - 1);
            chars = bigexB.data.at(0).str.size();
            bigex9.digitsPerNode = bigexB.digitsPerNode;
        }

        // produce 9s
        while(nodes > 0)
        {
            nodes--;
            bigex9.data.push_front(string(bigex9.digitsPerNode, '9'));
        }
        bigex9.data.push_front(string(chars, '9'));



        //cout << "bigex9 ";
        //bigex9.print(cout);
        //cout << endl;

        //cout << "bigexL ";
        //bigexL.print(cout);
        //cout << endl;

        Bigex step1 = sub_nocarry(bigex9, bigexL);
        //cout << "step1 ";
        //step1.print(cout);
        //cout << endl;

        Bigex step2 = add(step1, bigexS);
        //cout << "step2 ";
        //step2.print(cout);
        //cout << endl;

        int nodesY = step2.data.size() - 1;
        int nodes9 = bigex9.data.size() - 1;
        int charsY = step2.data.at(0).str.size();
        int chars9 = bigex9.data.at(0).str.size();

        if(nodesY > nodes9 || charsY > chars9)
        {
            // if # digits of step2 is > # digits of bigex9
            //cout << "# digits of step2 is > # digits of bigex9" << endl;

            //cout << "step2 ";
            //step2.print(cout);
            //cout << endl;

            Bigex temp(bigexA.digitsPerNode);
            // add nodes inbetween first and last
            for(int i = 1; i < step2.data.size() - 1; i++)
            {
                //cout << "push_back" << endl;
                temp.data.push_back(step2.data.at(i).str);
            }
            if(nodesY == nodes9)
            {
                // remove the carry from the first node
                int num = step2.data.at(0).num;
                num = num % (int)pow(10, chars9);
                if(nodesY > 0)
                {
                    // push num to front
                    //cout << "push_front" << endl;
                    if(num > 0)
                    {
                        temp.data.push_front(numtostring(num));
                    }
                    // add 1 to the last node
                    //cout << "push_back" << endl;
                    temp.data.push_back(numtostring(step2.data.at(step2.data.size() - 1).num + 1));
                }
                else
                {
                    //cout << "push_back" << endl;
                    temp.data.push_back(numtostring(num + 1));
                }
            }
            else
            {
                // add 1 to the last node
                //cout << "push_back" << endl;
                temp.data.push_back(numtostring(step2.data.at(step2.data.size() - 1).num + 1));
            }

            return temp;
        }
        else
        {
            // if # digits of step2 is <= # digits of bigex9
            //cout << "# digits of step2 is <= # digits of bigex9" << endl;

            Bigex step3 = sub_nocarry(bigex9, step2);
            //step3.print(cout);
            //cout << endl;
            if(which == BIG_A)
            {
                step3.isNegative = false;
            }
            else
            {
                if(step3.data.size() == 1 && step3.data.at(0).num == 0)
                {
                    step3.isNegative = false;
                }
                else
                {
                    step3.isNegative = true;
                }
            }

            return step3;
        }
    }

    Bigex sub_nocarry(Bigex bigexA, Bigex bigexB)
    {
        // Sign Manipulation
        if(!bigexA.isNegative && bigexB.isNegative)
        {
            // A - -B => A + B
            bigexA.isNegative = false;
            bigexB.isNegative = false;
            return add(bigexA, bigexB);
        }
        if(bigexA.isNegative && !bigexB.isNegative)
        {
            // -A - B => -A + -B
            bigexA.isNegative = true;
            bigexB.isNegative = true;
            return add(bigexA, bigexB);
        }
        if(bigexA.isNegative && bigexB.isNegative)
        {
            // -A - -B => -A + B => B - A
            bigexA.isNegative = false;
            bigexB.isNegative = false;
            return sub_nocarry(bigexB, bigexA);
        }

        Bigex result(digitsPerNode);

        int rollover = 0;
        int indexA = bigexA.data.size() - 1;
        int indexB = bigexB.data.size() - 1;

        while(indexA > -1 || indexB > -1)
        {
            //cout << "sub no carry" << endl;
            int a = 0;
            int b = 0;

            if(indexA > -1)
            {
                a = bigexA.data.at(indexA).num;
                indexA--;
            }
            if(indexB > -1)
            {
                b = bigexB.data.at(indexB).num;
                indexB--;
            }

            long long num = a - b + rollover;
            rollover = num / pow(10, digitsPerNode);
            num = num % (int)pow(10, digitsPerNode);

            string str = numtostring(num);

            // this says if we aren't on the last node, pad the string
            if(rollover > 0 || indexA > -1 || indexB > -1)
            {
                padzeros(str);
            }

            if(num > 0 || indexA > -1 || indexB > -1)
            {
                result.data.push_front(str);
            }
        }
        if(result.data.size() == 0)
        {
            result.data.push_front("0");
        }

        return result;
    }

    void padzeros(string & str) const
    {
        // create a new string with the proper amount of zeros
        string pad(digitsPerNode - str.size(), '0');
        str = pad + str;
    }
    string numtostring(long long num) const
    {
        string str;
        stringstream ss;
        ss << num;
        ss >> str;
        return str;
    }

    bool isNegative = false;
    DoubleLinkedList data;
    int digitsPerNode;
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

    void evaluatePostfix(int digitsPerNode)
    {
        string str;
        stringstream ss(postfix);
        stackType<Bigex> myStack;
        while(ss.good())
        {
            ss >> str;
            if(str.size() == 0)
            {
                continue;
            }
            if(str.size() == 1 && isOperator(str[0]))
            {
                char op = str[0];
                Bigex operand2 = myStack.top();
                myStack.pop();
                Bigex operand1 = myStack.top();
                myStack.pop();

                if(op == '+')
                {
                    myStack.push(operand1 + operand2);
                }
                else if(op == '-')
                {
                    myStack.push(operand1 - operand2);
                }
                else if(op == '*')
                {
                    myStack.push(operand1 * operand2);
                }
            }
            else
            {
                myStack.push(Bigex(str, digitsPerNode));
            }
        }
        cout << "\tResult ";
        myStack.top().print(cout);
        cout << endl;
    }
};

bool infixToPostfix::isOperator(const char c)
{
    if((c == '+') || (c == '-') || (c == '*') || (c == '/'))
        return true;
    else
        return false;
}

int infixToPostfix::precedence(const char op1, const char op2)
{
    int pre1 = 0, pre2 = 0; //declare variables to compare the precedence
    if((op1 == '^') || (op2 == '^'))
        cout << "Exponentiation was not considered for precedence. \n\tThe program may result in abnormal output of Postfix exp.";
    if((op1 == '+') || (op1 == '-')) //low precedence
        pre1 = 0;
    else if((op1 == '*') || (op1 == '/') || (op1 == '%'))
        pre1 = 1;                     //high precedence
    if((op2 == '+') || (op2 == '-')) //low precedence
        pre2 = 0;
    else if((op2 == '*') || (op2 == '/') || (op2 == '%'))
        pre2 = 1; //     high precedence

    //     compare and return the precedence of op1 & op2
    if(pre1 == pre2) //     equal precedence of op1 & op2
        return 0;
    else if(pre1 > pre2) //higher precedence of op1 over op2
        return 1;
    else //     lower precedence of op1 over op2
        return -1;
}

//     conversion of infix arithmetic exp into postfix exp
void infixToPostfix::showPostfix()
{
    stackType<char> myStack; //A Stack of characters
    string pfx = "";
    infix.append(")"); //append a right parenthesis ')' to the end of infix
    myStack.push('('); //push the left parenthesis onto the stack
    unsigned int i = 0;
    if((infix[i]) == '-')
        infix[i] = '~';
    do
    { //loop through the infix array 
        if(isOperator(infix[i]) && infix[i + 1] == '-')
        {
            infix[i + 1] = '~';
        }
        else if(isOperator(infix[i]) && infix[i + 1] == '+')
        {
            infix.erase(infix.begin() + i + 1);
        }
        else if(isOperator(infix[i]))
        { //If the operator is an element in the string
            pfx += ' ';
            if(!myStack.isEmptyStack() && isOperator(myStack.top()))
            { //when the top of the stack is an operator
                if(precedence(infix[i], myStack.top()) == 0)
                { //find the precedence of the operator
                    pfx = pfx + myStack.top(); //place the operator in postfix
                    myStack.pop();             //Pop the stack
                }
                else if(precedence(infix[i], myStack.top()) == 1)
                {
                    myStack.push(infix[i]); //push into stack the infix elem when higher precedence
                    i++;
                }
                else
                {
                    pfx = pfx + myStack.top(); //place the element in postfix & pop the stack
                    myStack.pop();
                }
            }
            else
            {
                myStack.push(infix[i]); //push onto stack when top of stack  is not an operator
                i++;
            }
        }
        else if(infix[i] == ')')
        {
            while(!myStack.isEmptyStack() && myStack.top() != '(')
            { //get the elements from the stack
                pfx += ' ';
                pfx = pfx + myStack.top();
                myStack.pop();
            }
            myStack.pop(); //pop the '(' from the stack
            i++;
        }
        else if(infix[i] == '(')
        {
            myStack.push(infix[i]); //neither operator nor operand push onto stack
            if(infix[i + 1] == '-')
            {
                infix.erase(infix.begin() + i + 1);
                pfx += '-';
            }
            else if(infix[i + 1] == '+')
            {
                infix.erase(infix.begin() + i + 1);
                pfx += '+';
            }
            i++;
        } //end if
        else
        {
            if(infix[i] == '~')
            {
                pfx += '-';
            }
            else
            {
                pfx = pfx + infix[i]; //In case of operands, copy the operands  from infix to postfix
            }
            i++;
        }
    }
    while(i < infix.length());
    cout << "\n\tPostfix Expression: " << pfx << endl;
    postfix = pfx;
}

// void print(Bigex *a, int size, ostream & out) {
//     a[0].print(out);
//     for (int i = 1; i < size; i++) {
//         out << endl;
//         a[i].print(out);
//     }
// }

int count_lines(string &filename, int digitsPerNode)
{
    std::ifstream ifs(filename.c_str());

    int counter = 0;
    while(!ifs.eof())
    {
        string line;
        ifs >> line;
        counter++;
    }
    return counter;
}

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        //std::cerr("Usage: infinitearithmetic \"input=xyz.txt;digitsPerNode=<number>\"\n");
        return 1;
    }
    ArgumentManager am(argc, argv);
    std::string filename = am.get("input");
    int digitsPerNode = std::stoi(am.get("digitsPerNode"));
    ifstream infile(filename, ios::in);

    //ifstream infile("10.txt", ios::in);
    //int digitsPerNode = 3;

    infixToPostfix InfixExp;
    string infix;
    if(!infile)
    {
        cout << "Cannot open input file. Program terminates!!!" << endl;
        return 1;
    }
    while(getline(infile, infix))
    {
        if(infix.empty() || infix.at(0) == '\n') { continue; }

        InfixExp.getInfix(infix);
        InfixExp.showInfix();
        //InfixExp.convert_sign();
        InfixExp.showPostfix();
        InfixExp.evaluatePostfix(digitsPerNode);
    }
    infile.close();
    return 0;
}