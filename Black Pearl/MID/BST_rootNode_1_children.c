#include <stdio.h>
#include <stdlib.h>

// Structure for a binary tree node
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to create a new node
struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a node into a Binary Search Tree (BST)
struct TreeNode* insertBST(struct TreeNode* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insertBST(root->left, data);
    } else if (data > root->data) {
        root->right = insertBST(root->right, data);
    }

    return root;
}

// Function to insert a node into a Binary Tree (BT)
struct TreeNode* insertBT(struct TreeNode* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (root->left == NULL) {
        root->left = insertBT(root->left, data);
    } else if (root->right == NULL) {
        root->right = insertBT(root->right, data);
    } else {
        // If both left and right children are present, insert in the left subtree
        root->left = insertBT(root->left, data);
    }

    return root;
}

// Function to delete the root node with one child in a BT
struct TreeNode* deleteRootNodeBT(struct TreeNode* root) {
    if (root == NULL) {
        return NULL;
    }

    // Determine which child exists
    struct TreeNode* child = (root->left != NULL) ? root->left : root->right;

    free(root);

    return child;
}

// Function to print inorder traversal of a binary tree
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

    printf("Choose the type of binary tree:\n");
    printf("1. Binary Search Tree (BST)\n");
    printf("2. Binary Tree (BT)\n");
    scanf("%d", &choice);

    while (1) {
        printf("\nBinary Tree Operations:\n");
        printf("1. Insert Element\n");
        printf("2. Delete Root Node with One Child\n");
        printf("3. Inorder Traversal\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to insert: ");
                scanf("%d", &data);
                if (root == NULL) {
                    root = createNode(data);
                } else {
                    if (choice == 1) {
                        root = insertBST(root, data);
                    } else {
                        root = insertBT(root, data);
                    }
                }
                break;
            case 2:
                if (root != NULL && ((root->left != NULL && root->right == NULL) || (root->left == NULL && root->right != NULL))) {
                    root = deleteRootNodeBT(root);
                    printf("Root node with one child deleted.\n");
                } else {
                    printf("Root node does not have exactly one child.\n");
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
