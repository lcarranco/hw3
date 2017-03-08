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
#include "ArgumentManager.h"

using namespace std;

struct Node
{
    long long num = 0;
    string str;
    Node* prev = 0;
    Node* next = 0;
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
            Node* deleteme = head;
            head = head->next;
            delete deleteme;
        }
    }

    // Copy constructor
    DoubleLinkedList(DoubleLinkedList const & list)
    {
        //cout << "DLL copy" << endl;
    }

    DoubleLinkedList & operator=(DoubleLinkedList const & other)
    {
        //cout << "DLL =" << endl;
        clear();

        Node* temp = other.head;
        while (temp != nullptr)
        {
            push_back(temp->str);
            temp = temp->next;
        }
        return *this;
    }

    void push_front(string parted)
    {
        Node*temp = new Node();
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
        Node* temp = new Node();
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

    void print(ostream & out) const
    {
        Node* temp = head;
        while (temp != nullptr)
        {
            out << temp->str;
            temp = temp->next;
        }
    }

    Node at(int index) const
    {
        int i = 0;
        Node* temp = head;
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
        Node* temp = head;
        while (temp != 0)
        {
            temp = temp->next;
            count++;
        }
        return count;
    }

    void swap(DoubleLinkedList & other)
    {
        Node* temp = head;
        head = other.head;
        other.head = temp;
    }

private:
    Node* head = 0;
    Node* tail = 0;
};

class Postfix_Infix
{
public:
    Postfix_Infix();
    ~Postfix_Infix();

private:
    
};

void print(BigNumber *a, int size, ostream & out)
{
    a[0].print(out);
    for (int i = 1; i < size; i++)
    {
        out << endl;
        a[i].print(out);
    }
}

class Stack
{
public:
    Stack();
    ~Stack();
    bool empty() const
    {

    }

    int size() const
    {

    }

    Stack & top()
    {

    }

    void push()
    {

    }

    Stack emplace()
    {

    }

    void pop()
    {

    }

    void swap()
    {
        
    }

private:
    
};

int count_lines(string & filename, int digitsPerNode)
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

void input(BigNumber *a, string & filename, int digitsPerNode)
{
    std::ifstream ifs(filename.c_str());

    int counter = 0;
    while (!ifs.eof())
    {
        string line;
        ifs >> line;
        if (line.size() != 0)
        {
            a[counter] = BigNumber(line, digitsPerNode);
            counter++;
        }
    }
}



int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        //std::cerr("Usage: infinitearithmetic \"input=xyz.txt;digitsPerNode=<number>\"\n");
        return 1;
    }
    ArgumentManager am(argc, argv);
    std::string filename = am.get("input");
    int digitsPerNode = std::stoi(am.get("digitsPerNode"));

    //Used for testing on Visual Studio
    //string filename = "1.txt";
    //int digitsPerNode = 8;
    //string algorithm = "quick";
    //string outfile = "out.txt";

    int size = count_lines(filename, digitsPerNode);
    BigNumber *a = new BigNumber[size];
    input(a, filename, digitsPerNode);

    return 0;
}