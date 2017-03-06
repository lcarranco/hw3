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
class BigNumber
{
public:
    BigNumber() {}
    ~BigNumber()
    {
        //cout << "BN ~" << endl;
    }

    BigNumber(string num, int digitsPerNode)
    {
        //cout << num << endl;
        if (num[0] == '-')
        {
            isNegative = true;
            num.erase(num.begin());
        }
        int startIndex = num.length() - digitsPerNode;
        while (startIndex >= 0)
        {
            data.push_front(num.substr(startIndex, digitsPerNode));
            startIndex -= digitsPerNode;
        }
        if (startIndex < 0)
        {
            data.push_front(num.substr(0, startIndex + digitsPerNode));
        }
    }
    BigNumber(BigNumber const & other)
    {
        //cout << "BN copy" << endl;
        isNegative = other.isNegative;
        data = other.data;
    }
    BigNumber & operator= (BigNumber const & other)
    {
        //cout << "BN =" << endl;
        isNegative = other.isNegative;
        data = other.data;
        return *this;
    }
    bool operator< (BigNumber const & other) const
    {
        BigNumber const & a = *this;
        BigNumber const & b = other;

        if (a.isNegative && !b.isNegative)
        {
            return true;
        }
        if (!a.isNegative && b.isNegative)
        {
            return false;
        }

        bool result = false;
        if (a.data.size() < b.data.size())
        {
            //return true;
            result = true;
        }
        else
            if (a.data.size() > b.data.size())
            {
                //return false;
                result = false;
            }
            else
                if (a.data.size() == b.data.size())
                {
                    int index = 0;
                    while (index < a.data.size())
                    {
                        if (a.data.at(index).num < b.data.at(index).num)
                        {
                            //return true;
                            result = true;
                            break;
                        }
                        if (a.data.at(index).num > b.data.at(index).num)
                        {
                            //return false;
                            result = false;
                            break;
                        }
                        if (a.data.at(index).num == b.data.at(index).num)
                        {
                            //Go to the next node
                        }
                        index++;
                    }
                }
        if (isNegative)
        {
            result = !result;
        }
        return result;
    }

    void print(ostream & out) const
    {
        if (isNegative)
        {
            out << "-";
        }
        data.print(out);
    }

    void swap(BigNumber & other)
    {
        std::swap(isNegative, other.isNegative);
        data.swap(other.data);
    }
    // bool operator>= (BigNumber const & other) const
    // {
    //     return !operator< (other);
    // }

private:
    bool isNegative = false;
    DoubleLinkedList data;
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
    std::string algorithm = am.get("algorithm");
    int digitsPerNode = std::stoi(am.get("digitsPerNode"));
    std::string outfile = am.get("output");
    cout << outfile << endl;

    //Used for testing on Visual Studio
    //string filename = "1.txt";
    //int digitsPerNode = 8;
    //string algorithm = "quick";
    //string outfile = "out.txt";

    int size = count_lines(filename, digitsPerNode);
    BigNumber *a = new BigNumber[size];
    input(a, filename, digitsPerNode);

    fstream output(outfile, fstream::out);
    print(a, size, output);
    output.close();

    return 0;
}