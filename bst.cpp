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

    if (value < root->data) {
        root->left = insertNode(root->left, value);
    } else if (value > root->data) {
        root->right = insertNode(root->right, value);
    }

    return root;
}

Node* findMin(Node* root) {
    while (root && root->left) {
        root = root->left;
    }
    return root;
}

Node* deleteNode(Node* root, int value) {
    if (!root) return root;

    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    } else {
        if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
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

bool search(Node* root, int value) {
    if (!root) return false;

    if (root->data == value) {
        return true;
    } else if (value < root->data) {
        return search(root->left, value);
    } else {
        return search(root->right, value);
    }
}

void levelOrderTraversal(Node* root) {
    if (!root) return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        cout << current->data << " ";

        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
}

int main() {
    Node* root = nullptr;

    root = insertNode(root, 50);
    root = insertNode(root, 30);
    root = insertNode(root, 70);
    root = insertNode(root, 20);
    root = insertNode(root, 40);
    root = insertNode(root, 60);
    root = insertNode(root, 80);

    cout << "In-order Traversal (BST): ";
    inorderTraversal(root);
    cout << endl;

    cout << "Deleting node 70." << endl;
    root = deleteNode(root, 70);
    cout << "In-order Traversal after Deletion: ";
    inorderTraversal(root);
    cout << endl;

    int searchKey = 40;
    if (search(root, searchKey)) {
        cout << "Value " << searchKey << " found in BST." << endl;
    } else {
        cout << "Value " << searchKey << " not found in BST." << endl;
    }

    cout << "BFS (Level-wise Traversal): ";
    levelOrderTraversal(root);
    cout << endl;

    return 0;
}
