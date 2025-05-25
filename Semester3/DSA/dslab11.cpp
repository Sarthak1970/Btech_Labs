#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* insert(Node* root, int val) {
    if (root == NULL) {
        root = new Node();
        root->data = val;
        root->left = root->right = NULL;
    } else if (val < root->data) {
        root->left = insert(root->left, val);
    } else {
        root->right = insert(root->right, val);
    }
    return root;
}

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

void preorder(Node* root) {
    if (root != NULL) {
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }
}

Node* findMin(Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

Node* deleteNode(Node* root, int val) {
    if (root == NULL) {
        return root;
    }
    if (val < root->data) {
        root->left = deleteNode(root->left, val);
    } else if (val > root->data) {
        root->right = deleteNode(root->right, val);
    } else {
        if (root->left == NULL && root->right == NULL) {
            delete root;
            root = NULL;
        }
        else if (root->left == NULL) {
            Node* temp = root;
            root = root->right;
            delete temp;
        } else if (root->right == NULL) {
            Node* temp = root;
            root = root->left;
            delete temp;
        }

        else {
            Node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }
    return root;
}

int main() {
    Node* tree = NULL;
    int choice, value;

    do {
        cout << "\n1. Insert an element\n2. Inorder Traversal\n3. Preorder Traversal\n4. Postorder Traversal\n5. Delete a node\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                tree = insert(tree, value);
                break;

            case 2:
                cout << "Inorder traversal: ";
                inorder(tree);
                cout << endl;
                break;

            case 3:
                cout << "Preorder traversal: ";
                preorder(tree);
                cout << endl;
                break;

            case 4:
                cout << "Postorder traversal: ";
                postorder(tree);
                cout << endl;
                break;

            case 5:
                cout << "Enter value to delete: ";
                cin >> value;
                tree = deleteNode(tree, value);
                break;

            case 6:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}
