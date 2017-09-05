/***********************************************************************
* Module:
*    Week 02, Stack
*    Brother Helfrich, CS 235
* Author:
*    Brother Helfrich & John Wood & Etienne Beaulac
* Summary:
*    This program will implement the testInfixToPostfix()
*    and testInfixToAssembly() functions
************************************************************************/

#include <iostream>    // for ISTREAM and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "stack.h"     // for STACK
using std::cout;
using std::string;
using std::cin;
using std::getline;
using std::endl;
using namespace custom;

// function prototypes
bool smallerEqualTo(string infix, char stack);
void splitInfix(const string & infix, string(&nInfix)[50], int & numTokens);

/*****************************************************
* CONVERT INFIX TO POSTFIX
* Convert infix equation "5 + 2" into postifx "5 2 +"
*****************************************************/
string convertInfixToPostfix(const string & infix)
{
	
	int numTokens = 0;
	string postfix;
	string nInfix[50];
	splitInfix(infix, nInfix, numTokens);
	stack <char> tStack;

	
	postfix += ' ';
	for (int i = 0; i < numTokens; i++)
	{
		try
		{
			if (isdigit(nInfix[i][0]) || isalpha(nInfix[i][0])
				|| nInfix[i][0] == '.' || nInfix[i][0] == '_')	// alphanumeric
			{
				postfix += nInfix[i];
				postfix += ' ';
			}
			else if (nInfix[i][0] == '(')						// open parenthesis
			{
				tStack.push(nInfix[i][0]);
			}
			else if (nInfix[i][0] == ')')						// close parenth.
			{
				while (tStack.top() != '(')						// loop for parenth
				{
					postfix += tStack.top();
					postfix += ' ';
					tStack.pop();
				}
				tStack.pop();
			}
			else												// Operators
			{
				while (!tStack.empty() && smallerEqualTo(nInfix[i], tStack.top())
					&& tStack.top() != '(')
				{
					postfix += tStack.top();
					postfix += ' ';
					tStack.pop();
				}
				tStack.push(nInfix[i][0]);
			}
		}
		catch (const char * error)
		{

		}
	} // FOR loop

	while (!tStack.empty())									// Empty the stack
	{
		postfix += tStack.top();
		tStack.pop();
		if (!tStack.empty())
			postfix += ' ';
	}
	return postfix;
}

/*****************************************************
* SPLIT INFIX TO WORDS
* Splits the infix given by user into seperate words
*****************************************************/
void splitInfix(const string & infix, string (&nInfix)[50], int & numTokens)
{
	string temp;
	for (int i = 0; i < infix.length(); i++)
	{
		if (isdigit(infix[i]) || isalpha(infix[i]) || infix[i] == '.'
			|| infix[i] == '_')			  // see if alphanumeric
			temp += infix[i];			  // put in temp if word
		else if (infix[i] == ' ')		  // see if space -> ignore
			continue;
		else							  // see if anything else (operators)
		{
			if (!temp.empty())			  // if there's a word put into infix
			{
				nInfix[numTokens] = temp;
				numTokens++;
				temp.clear();
			}
			nInfix[numTokens] = infix[i]; // put operator into infix
			numTokens++;
		}
	}
	if (!temp.empty())					  // anything else remaining into infix
	{
		nInfix[numTokens] = temp;
		numTokens++;
	}
}

/*****************************************************
* SMALLER OR EQUAL TO
* Transforms the chars into order of operations and 
* determines if infix is smaller or equal to stack.top()
*****************************************************/
bool smallerEqualTo(string infix, char stack)
{
	char inf = infix[0];				// Convert string to char for switch
	int intInf = 0;
	int intStack = 0;
	switch (inf)
	{
	case '^':
		intInf = 2;
		break;
	case '%':
	case '*':
	case '/':
		intInf = 1;
		break;
	case '+':
	case '-':
		intInf = 0;
		break;
	default:
		break;
	}
	switch (stack)
	{
	case '^':
		intStack = 2;
		break;
	case '%':
	case '*':
	case '/':
		intStack = 1;
		break;
	case '+':
	case '-':
		intStack = 0;
		break;
	default:
		break;
	}
	return intInf <= intStack;
}

/*****************************************************
* TEST INFIX TO POSTFIX
* Prompt the user for infix text and display the
* equivalent postfix expression
*****************************************************/
void testInfixToPostfix()
{
	string input;
	cout << "Enter an infix equation.  Type \"quit\" when done.\n";

	do
	{
		// handle errors
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
		}

		// prompt for infix
		cout << "infix > ";
		getline(cin, input);

		// generate postfix
		if (input != "quit")
		{
			string postfix = convertInfixToPostfix(input);
			cout << "\tpostfix: " << postfix << endl << endl;
		}
	} while (input != "quit");
}

/**********************************************
* CONVERT POSTFIX TO ASSEMBLY
* Convert postfix "5 2 +" to assembly:
*     LOAD 5
*     ADD 2
*     STORE VALUE1
**********************************************/
string convertPostfixToAssembly(const string & postfix)
{
	string assembly;

	return assembly;
}

/*****************************************************
* TEST INFIX TO ASSEMBLY
* Prompt the user for infix text and display the
* resulting assembly instructions
*****************************************************/
void testInfixToAssembly()
{
	string input;
	cout << "Enter an infix equation.  Type \"quit\" when done.\n";

	do
	{
		// handle errors
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
		}

		// prompt for infix
		cout << "infix > ";
		getline(cin, input);

		// generate postfix
		if (input != "quit")
		{
			string postfix = convertInfixToPostfix(input);
			cout << convertPostfixToAssembly(postfix);
		}
	} while (input != "quit");

}
