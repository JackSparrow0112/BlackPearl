#include <stdio.h>
#include <stdlib.h>

// Structure for a binary tree node
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Structure for a stack node
struct StackNode {
    struct TreeNode* data;
    struct StackNode* next;
};

// Structure for a stack
struct Stack {
    struct StackNode* top;
};

// Function to create a new tree node
struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to create an empty stack
struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = NULL;
    return stack;
}

// Function to push a tree node onto the stack
void push(struct Stack* stack, struct TreeNode* treeNode) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    newNode->data = treeNode;
    newNode->next = stack->top;
    stack->top = newNode;
}

// Function to check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == NULL;
}

// Function to pop a tree node from the stack
struct TreeNode* pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        return NULL;
    }
    struct StackNode* temp = stack->top;
    struct TreeNode* data = temp->data;
    stack->top = temp->next;
    free(temp);
    return data;
}

// Function for non-recursive inorder traversal
void inorder(struct TreeNode* root) {
    struct Stack* stack = createStack();
    struct TreeNode* currentNode = root;

    while (currentNode || !isEmpty(stack)) {
        while (currentNode) {
            push(stack, currentNode);
            currentNode = currentNode->left;
        }

        currentNode = pop(stack);
        printf("%d ", currentNode->data);

        currentNode = currentNode->right;
    }

    free(stack);
}

// Function for non-recursive preorder traversal
void preorder(struct TreeNode* root) {
    struct Stack* stack = createStack();
    push(stack, root);

    while (!isEmpty(stack)) {
        struct TreeNode* currentNode = pop(stack);
        printf("%d ", currentNode->data);

        if (currentNode->right) {
            push(stack, currentNode->right);
        }
        if (currentNode->left) {
            push(stack, currentNode->left);
        }
    }

    free(stack);
}

// Function for non-recursive postorder traversal
void postorder(struct TreeNode* root) {
    struct Stack* stack1 = createStack();
    struct Stack* stack2 = createStack();
    push(stack1, root);

    while (!isEmpty(stack1)) {
        struct TreeNode* currentNode = pop(stack1);
        push(stack2, currentNode);

        if (currentNode->left) {
            push(stack1, currentNode->left);
        }
        if (currentNode->right) {
            push(stack1, currentNode->right);
        }
    }

    while (!isEmpty(stack2)) {
        struct TreeNode* currentNode = pop(stack2);
        printf("%d ", currentNode->data);
    }

    free(stack1);
    free(stack2);
}

int main() {
    struct TreeNode* root = NULL;
    int choice, data;

    while (1) {
        printf("\nBinary Tree Operations:\n");
        printf("1. Insert Element\n");
        printf("2. Non-Recursive Inorder Traversal\n");
        printf("3. Non-Recursive Preorder Traversal\n");
        printf("4. Non-Recursive Postorder Traversal\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to insert: ");
                scanf("%d", &data);
                root = insert(root, data);
                break;
            case 2:
                printf("Non-Recursive Inorder Traversal: ");
                inorder(root);
                printf("\n");
                break;
            case 3:
                printf("Non-Recursive Preorder Traversal: ");
                preorder(root);
                printf("\n");
                break;
            case 4:
                printf("Non-Recursive Postorder Traversal: ");
                postorder(root);
                printf("\n");
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
