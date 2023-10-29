#include <iostream>

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    Node* root;

    Node* insert(Node* root, int data) {
        if (root == nullptr) {
            return new Node(data);
        }

        if (data < root->data) {
            root->left = insert(root->left, data);
        }
        else if (data > root->data) {
            root->right = insert(root->right, data);
        }

        return root;
    }

    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* remove(Node* root, int data) {
        if (root == nullptr) {
            return root;
        }

        if (data < root->data) {
            root->left = remove(root->left, data);
        }
        else if (data > root->data) {
            root->right = remove(root->right, data);
        }
        else {
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            Node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = remove(root->right, temp->data);
        }

        return root;
    }

    bool search(Node* root, int data) {
        if (root == nullptr) {
            return false;
        }

        if (data == root->data) {
            return true;
        }
        else if (data < root->data) {
            return search(root->left, data);
        }
        else {
            return search(root->right, data);
        }
    }

    int getHeight(Node* node) {
        if (node == nullptr) {
            return 0;
        }

        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);

        return 1 + std::max(leftHeight, rightHeight);
    }

    bool isBalanced(Node* node) {
        if (node == nullptr) {
            return true;
        }

        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);

        if (abs(leftHeight - rightHeight) <= 1 &&
            isBalanced(node->left) &&
            isBalanced(node->right)) {
            return true;
        }

        return false;
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(int data) {
        root = insert(root, data);
    }

    void remove(int data) {
        root = remove(root, data);
    }

    bool search(int data) {
        return search(root, data);
    }

    void inorderTraversal(Node* node) {
        if (node == nullptr) {
            return;
        }
        inorderTraversal(node->left);
        std::cout << node->data << " ";
        inorderTraversal(node->right);
    }

    void inorder() {
        inorderTraversal(root);
        std::cout << std::endl;
    }

    int getHeight() {
        return getHeight(root);
    }

    bool isBalanced() {
        return isBalanced(root);
    }
};

int main() {
    BinarySearchTree bst;

    bst.insert(50);
    bst.insert(30);
    bst.insert(20);
    bst.insert(40);
    bst.insert(70);
    bst.insert(60);
    bst.insert(80);

    std::cout << "Inorder Traversal: ";
    bst.inorder();
    
    std::cout << "Height of the tree: " << bst.getHeight() << std::endl;

    if (bst.isBalanced()) {
        std::cout << "The tree is balanced." << std::endl;
    } else {
        std::cout << "The tree is not balanced." << std::endl;
    }

    bst.remove(30);
    bst.remove(80);

    std::cout << "Inorder Traversal after removing nodes: ";
    bst.inorder();

    return 0;
}
