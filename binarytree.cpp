#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

Node* insertNode(Node* root, int value) {
    if (!root) {
        return new Node(value);
    }

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();

        if (!temp->left) {
            temp->left = new Node(value);
            break;
        } else {
            q.push(temp->left);
        }

        if (!temp->right) {
            temp->right = new Node(value);
            break;
        } else {
            q.push(temp->right);
        }
    }
    return root;
}

void inorderTraversal(Node* root) {
    if (root) {
        inorderTraversal(root->left);
        cout << root->data << " ";
        inorderTraversal(root->right);
    }
}

int findDepth(Node* root) {
    if (!root) return 0;

    int leftDepth = findDepth(root->left);
    int rightDepth = findDepth(root->right);

    return max(leftDepth, rightDepth) + 1;
}

void displayLeafNodes(Node* root) {
    if (!root) return;

    if (!root->left && !root->right) {
        cout << root->data << " ";
        return;
    }

    if (root->left) displayLeafNodes(root->left);
    if (root->right) displayLeafNodes(root->right);
}

Node* copyTree(Node* root) {
    if (!root) return nullptr;

    Node* newRoot = new Node(root->data);
    newRoot->left = copyTree(root->left);
    newRoot->right = copyTree(root->right);

    return newRoot;
}

int main() {
    Node* root = nullptr;

    root = insertNode(root, 10);
    root = insertNode(root, 20);
    root = insertNode(root, 30);
    root = insertNode(root, 40);
    root = insertNode(root, 50);
    root = insertNode(root, 60);

    cout << "In-order Traversal of Tree: ";
    inorderTraversal(root);
    cout << endl;

    cout << "Depth of the Tree: " << findDepth(root) << endl;

    cout << "Leaf Nodes: ";
    displayLeafNodes(root);
    cout << endl;

    Node* copiedTree = copyTree(root);
    cout << "In-order Traversal of Copied Tree: ";
    inorderTraversal(copiedTree);
    cout << endl;

    return 0;
}