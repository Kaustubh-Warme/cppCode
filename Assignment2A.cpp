#include <iostream>
#include <stack>
#include <cctype>
using namespace std;


struct Node
{
	char data;
	Node * left;
	Node * right;
	
	Node(char value)
	{
		data = value;
		left = right = nullptr;
	}
};

Node * constructTree(string postfix)
{
	stack<Node*> s;
	
	for(char ch : postfix)
	{
		if(isalnum(ch))
			s.push(new Node(ch));
		else
		{
			Node * right = s.top();
			s.pop();
			Node * left = s.top();
			s.pop();
			
			Node * newNode = new Node(ch);
			newNode->left = left;
			newNode->right = right;
			s.push(newNode);
		}
	}
	
	return s.top();
}


void inorderNonRecursive(Node * root)
{
	stack<Node*> s;
	
	Node * current = root;
	
	while(current!=nullptr || !s.empty())
	{
		while(current!=nullptr)
		{
			s.push(current);
			current = current->left;
		}
		
		
		current = s.top();
		s.pop();
		
		cout << current->data << " ";
		
		current = current->right;
	}
}


int main()
{	
	string expression;
	cout << "\nEnter a postfix expression: ";
	cin >>	expression;
	
	Node * expressionRoot = constructTree(expression);
	
	cout << "\nIn-Order Traversal: ";
	inorderNonRecursive(expressionRoot);
	cout << endl << endl;
	
	return 0;
}
