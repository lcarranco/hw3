#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <stack>
#include <cassert>
using namespace std;
#define MAX 100

class infixToPostfix
{
public:
	void convertToPostfix();
	bool precedence(char opr1, char opr2);
	void getInfix(string);
	void showInfix();
	void showPostfix();
	infixToPostfix(string = ""); //Default constructor
		
private:
	string  ifx;
	string  pfx;
};
void infixToPostfix::convertToPostfix()
{
    pfx="";
    stack<char> someStack; //gonna just use an stl stack
    for(const char& symbol:ifx){

        if(symbol=='(') {
            someStack.push(symbol);
        }
        else if(symbol==')'){
            while(someStack.top()!='('){
                pfx+=someStack.top();
                someStack.pop();
            }
            someStack.pop(); //we don't need (
        }
        else if(symbol=='+'||symbol=='-'||symbol=='/'||symbol=='*'||symbol=='^') {
            while( !someStack.empty() && (someStack.top()!='(') && precedence(someStack.top(),symbol) ){
                pfx+=someStack.top();
                someStack.pop();
            }
            someStack.push(symbol);
        }
        else{
            pfx+=symbol;
        }
    }
   //remove leftover operators
    while (!someStack.empty()){
        pfx+=someStack.top();
        someStack.pop();
    }
    
} 

bool infixToPostfix::precedence(char opr1, char opr2)
{
    int prec1, prec2;

    if(opr1 == '*' || opr1 =='/')
        prec1 = 2;
    else
        if(opr1 == '+' || opr1 == '-')
            prec1 = 1;
        else
            if(opr1 ='(')
                prec1 = 0;


    if(opr2 == '*' || opr2 == '/')
        prec2 = 2;
    else
        if(opr2 =='+' || opr2 == '-')
            prec2 = 1;

    return(prec1 >= prec2);
}//end precedence

void infixToPostfix::getInfix(string data)
{
    ifx = data;
    convertToPostfix();
}


void infixToPostfix::showInfix()
{
    cout<<"infix: "<<ifx<<endl;
}


void infixToPostfix::showPostfix()
{
    cout<<"postfix: "<<pfx<<endl;
}

infixToPostfix::infixToPostfix(string infx)
{
    ifx = infx;
    convertToPostfix();
}


int main(){

infixToPostfix  InfixExp;

string infix;
ifstream infile;
infile.open("infixData.txt");
if(!infile){
cout << "Cannot open input file. Program terminates!!!" << endl; return 1;}

getline(infile,infix);

while(infile)
{
InfixExp.getInfix(infix);
InfixExp.showInfix();
InfixExp.showPostfix();
cout << endl;
getline(infile,infix);
}

infile.close();


return 0;}
