#include <stdio.h>
#include <stdlib.h>

// Structure for a binary tree node
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
    int height; // Height of the node
};

// Function to create a new node
struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1; // New node is initially added at the leaf level
    return newNode;
}

// Function to calculate the height of a node
int getHeight(struct TreeNode* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

// Function to calculate the balance factor of a node
int getBalanceFactor(struct TreeNode* node) {
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

// Function to perform a right rotation
struct TreeNode* rightRotate(struct TreeNode* y) {
    struct TreeNode* x = y->left;
    struct TreeNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = 1 + (getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right));
    x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));

    return x;
}

// Function to perform a left rotation
struct TreeNode* leftRotate(struct TreeNode* x) {
    struct TreeNode* y = x->right;
    struct TreeNode* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));
    y->height = 1 + (getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right));

    return y;
}

// Function to insert a node into an AVL tree
struct TreeNode* insertAVL(struct TreeNode* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insertAVL(root->left, data);
    } else if (data > root->data) {
        root->right = insertAVL(root->right, data);
    } else {
        // Duplicate data is not allowed in this example
        return root;
    }

    // Update height of the current node
    root->height = 1 + (getHeight(root->left) > getHeight(root->right) ? getHeight(root->left) : getHeight(root->right));

    // Get the balance factor to check for AVL balance
    int balance = getBalanceFactor(root);

    // Perform rotations if necessary to maintain AVL balance
    // Right Right Case
    if (balance > 1 && data < root->left->data) {
        return rightRotate(root);
    }
    // Left Left Case
    if (balance < -1 && data > root->right->data) {
        return leftRotate(root);
    }
    // Left Right Case
    if (balance > 1 && data > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // Right Left Case
    if (balance < -1 && data < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to perform inorder traversal of an AVL tree
void inorderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}

int main() {
    struct TreeNode* root = NULL;
    int choice, data;

    while (1) {
        printf("\nAVL Tree Operations:\n");
        printf("1. Insert Element\n");
        printf("2. Get Balance Factor\n");
        printf("3. Inorder Traversal\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to insert: ");
                scanf("%d", &data);
                root = insertAVL(root, data);
                break;
            case 2:
                printf("Enter the element to get balance factor: ");
                scanf("%d", &data);
                struct TreeNode* nodeToCheck = root;
                while (nodeToCheck != NULL) {
                    if (data == nodeToCheck->data) {
                        int balanceFactor = getBalanceFactor(nodeToCheck);
                        printf("Balance Factor for %d is %d\n", data, balanceFactor);
                        break;
                    } else if (data < nodeToCheck->data) {
                        nodeToCheck = nodeToCheck->left;
                    } else {
                        nodeToCheck = nodeToCheck->right;
                    }
                }
                if (nodeToCheck == NULL) {
                    printf("Element not found in the AVL tree.\n");
                }
                break;
            case 3:
                printf("Inorder Traversal: ");
                inorderTraversal(root);
                printf("\n");
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
