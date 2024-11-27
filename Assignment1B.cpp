#include <iostream>
using namespace std;

struct Node 
{
	int data;
	Node * left;
	Node * right;
	
	Node(int value)
	{
		data = value;
		left = right = nullptr;
	}
};


Node * insert(Node* root, int value)
{
	if(root == nullptr)
		return new Node(value);
	else
	{	if(value < root->data)
			root->left = insert(root->left, value);
		else
			root->right = insert(root->right, value);
	}
}


void display(Node * root)
{
	if(root != nullptr)
	{
		display(root->left);
		cout << root->data << " ";
		display(root->right);
	}
}


int findDepth(Node * root)
{
	if(root == nullptr)
		return 0;
	
	int leftDepth = findDepth(root->left);
	int rightDepth = findDepth(root->right);
	
	return 1 + max(leftDepth, rightDepth);
}

void displayLeafNodes(Node * root)
{
	if(root ==nullptr)
		return;
	
	if(root->left==nullptr	&&  root->right==nullptr)
		cout << root->data << " ";
	
	displayLeafNodes(root->left);
	displayLeafNodes(root->right);
}

Node * copyTree(Node* root)
{
	if(root==nullptr)
		return nullptr;
	
	Node * newNode = new Node(root->data);
	newNode->left = copyTree(root->left);
	newNode->right = copyTree(root->right);
	
	return newNode;
}


int doMenu()
{
	int choice;
	
	cout << "\n------------------Menu------------------" << endl;
	cout << "1. Insert into Tree       				 " << endl;
	cout << "2. Display Tree 						 " << endl;
	cout << "3. Find Depth of Tree 					 " << endl;
	cout << "4. Display Leaf Node of Tree 			 " << endl;
	cout << "5. Create a copy of Tree 				 " << endl;
	cout << "0. Quit								 " << endl << endl;
	
	cout << "Enter your choice: ";
	cin >> choice;
	return choice;
}


int main()
{
	//creating binary tree
	Node* myRoot = nullptr;
	Node* newRoot = nullptr;
	
	myRoot = insert(myRoot, 5);
	myRoot = insert(myRoot, 3);
	myRoot = insert(myRoot, 7);
	myRoot = insert(myRoot, 2);
	myRoot = insert(myRoot, 4);
	myRoot = insert(myRoot, 6);
	myRoot = insert(myRoot, 8);
	
	
	bool endProgram = false;
	
	while(!endProgram)
	{
		int choice = doMenu();
		
		switch(choice)
		{
			case 0:
				cout << "\n\nExiting Program..." << endl;
				endProgram = true;
				break;
			
			case 1:
				int newValue;
				cout << "\n\nEnter new value to insert: ";
				cin >> newValue;
				myRoot = insert(myRoot, newValue);
				cout << endl;
				cout << newValue << " as been insrted into the tree" << endl << endl;
				break;
	
			case 2:
				cout << "\n\nDisplaying Tree (In-Order Sequence): " << endl;
				display(myRoot);
				break;
				
			case 3:
				cout << "\n\nDepth of the tree is : " << findDepth(myRoot) << endl;
				break;
				
			case 4:
				cout << "\n\nLeaf nodes of the tree: " << endl;
				displayLeafNodes(myRoot);
				break;
				
			case 5:
				cout << "\n\nCreating copy of the tree: " << endl;
				cout << "Original Tree: " << endl;
				display(myRoot);
				newRoot = copyTree(myRoot);
				
				cout << "\nCopied Tree: " << endl;
				display(newRoot);
				break;
			
			default: 
				cout << "Error in Choice" << endl ;
				endProgram = true;
				break;
		}
		
	}
	
	
	return 0;
}