#include <iostream>
#include <stack>
#include <cctype>
using namespace std;

struct Node {
    char data;
    Node* left;
    Node* right;

    Node(char value) : data(value), left(nullptr), right(nullptr) {}
};

bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

Node* constructExpressionTree(const string& postfix) {
    stack<Node*> s;

    for (char ch : postfix) {
        if (isOperator(ch)) {
            Node* opNode = new Node(ch);

            opNode->right = s.top();
            s.pop();
            opNode->left = s.top();
            s.pop();

            s.push(opNode);
        } 
		else if (isalnum(ch)) {
            s.push(new Node(ch)); 
        }
    }

    return s.top();
}

void inOrderTraversal(Node* root) {
    stack<Node*> s;
    Node* current = root;

    while (current || !s.empty()) {
        while (current) {
            s.push(current);
            current = current->left;
        }
        current = s.top();
        s.pop();
        cout << current->data << " ";
        current = current->right;
    }
}

void preOrderTraversal(Node* root) {
    if (!root) return;

    stack<Node*> s;
    s.push(root);

    while (!s.empty()) {
        Node* current = s.top();
        s.pop();
        cout << current->data << " ";

        if (current->right) s.push(current->right);
        if (current->left) s.push(current->left);
    }
}

void postOrderTraversal(Node* root) {
    if (!root) return;

    stack<Node*> s1, s2;
    s1.push(root);

    while (!s1.empty()) {
        Node* current = s1.top();
        s1.pop();
        s2.push(current);

        if (current->left) s1.push(current->left);
        if (current->right) s1.push(current->right);
    }

    while (!s2.empty()) {
        cout << s2.top()->data << " ";
        s2.pop();
    }
}

int main() {
    string postfix = "ab+c*de/-";

    cout << "Postfix Expression: " << postfix << endl;

    Node* root = constructExpressionTree(postfix);

    cout << "In-order Traversal: ";
    inOrderTraversal(root);
    cout << endl;

    cout << "Pre-order Traversal: ";
    preOrderTraversal(root);
    cout << endl;

    cout << "Post-order Traversal: ";
    postOrderTraversal(root);
    cout << endl;

    return 0;
}
