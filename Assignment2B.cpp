#include <iostream>
#include <stack>
#include <cctype>
#include <string>

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


//construct expression tree
Node* constructTree(string postfix)
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


//Non-recursive Inorder traversal
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
		
		cout << current->data << " " ;
		current = current->right;
	}
}

void preorderNonRecursive(Node * root)
{
	if(root == nullptr)
		return;
	
	stack<Node*> s;
	s.push(root);
	
	while(!s.empty())
	{
		Node * current = s.top();
		s.pop();
		
		cout << current->data << " ";
		
		if(current->right)
			s.push(current->right);
		if(current->left)
			s.push(current->left);
	}
}



//Non-Recursive Post-order
void postorderNonRecursive(Node * root)
{
	if(root==nullptr)
		return;
	
	stack<Node*> s1, s2;
	s1.push(root);
	
	while(!s1.empty())
	{
		Node * current = s1.top();
		s1.pop();
		s2.push(current);
		
		if(current->left)
			s1.push(current->left);
		if(current->right)
			s2.push(current->right);
	}
	
	while(!s2.empty())
	{
		cout << s2.top()->data << " " ;
		s2.pop();
	}
}


int doMenu()
{	
	int choice;
	
	cout << "\n----------------Menu----------------" << endl;
	cout << "1. Post-order Sequence				   " << endl;
	cout << "2. Pre-order Sequence				   " << endl;
	cout << "3. In-order Sequence				   " << endl;
	cout << "0. Quit							   " << endl << endl;;
	
	cout << "Enter your choice: ";
	cin >> choice;
	
	return choice;
}


int main()
{	
	string expression;
	cout << "Enter expression (postfix): ";
	cin	>> expression;
	
	Node * expressionRoot = constructTree(expression);
	
	bool endMenu = false;
	
	while(!endMenu)
	{	
		int choice = doMenu();
		
		switch(choice)
		{
			
			
			case 3:
				cout << "In-order sequence: ";
				inorderNonRecursive(expressionRoot);
				cout << endl;
				break;
			
			case 2:
				cout << "Pre-order sequence: ";
				preorderNonRecursive(expressionRoot);
				cout << endl;
				break;
			
			case 1:
				cout << "Post-order sequence: ";
				postorderNonRecursive(expressionRoot);
				cout << endl;
				break;
				
			case 0:
				cout << "Exiting..." << endl;
				endMenu = true;
				break;
			
			default:
				cout << "Incorrect input for choice;" << endl;
				endMenu = true;
				break;
		}
	}
	
	
	
	return 0;
}