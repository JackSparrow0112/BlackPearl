#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100
struct TreeNode {
int data;
struct TreeNode* left;
struct TreeNode* right;
};
struct TreeNode* create_tree(int data) {
struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct
TreeNode));
newNode->data = data;
newNode->left = NULL;
newNode->right = NULL;
return newNode;
}
struct TreeNode* insert_node(struct TreeNode* root, int data) {
if (root == NULL) {
return create_tree(data);
}
struct TreeNode* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;
queue[++rear] = root;
while (front != rear) {
struct TreeNode* current = queue[++front];
if (current->left == NULL) {
current->left = create_tree(data);
break;
} else {
queue[++rear] = current->left;
}
if (current->right == NULL) {
current->right = create_tree(data);
break;
} else {
queue[++rear] = current->right;
}
}
return root;
}
void inorder_traversal(struct TreeNode* root) {
if (root != NULL) {
inorder_traversal(root->left);
printf("%d ", root->data);
inorder_traversal(root->right);
}
}
void preorder_traversal(struct TreeNode* root) {
if (root != NULL) {
printf("%d ", root->data);
preorder_traversal(root->left);
preorder_traversal(root->right);
}
}
void postorder_traversal(struct TreeNode* root) {
if (root != NULL) {
postorder_traversal(root->left);
postorder_traversal(root->right);
printf("%d ", root->data);
}
}
int get_height(struct TreeNode* root) {
if (root == NULL) {
return 0;
}
int left_height = get_height(root->left);
int right_height = get_height(root->right);
return (left_height > right_height) ? (left_height + 1) : (right_height +
1);
}
void mirror_image(struct TreeNode* root) {
if (root != NULL) {
struct TreeNode* temp = root->left;
root->left = root->right;
root->right = temp;
mirror_image(root->left);
mirror_image(root->right);
}
}
void print_leaf_nodes(struct TreeNode* root) {
if (root == NULL) {
return;
}
if (root->left == NULL && root->right == NULL) {
printf("%d ", root->data);
}
print_leaf_nodes(root->left);
print_leaf_nodes(root->right);
}
int count_nodes(struct TreeNode* root) {
if (root == NULL) {
return 0;
}
return 1 + count_nodes(root->left) + count_nodes(root->right);
}
void level_order_traversal(struct TreeNode* root) {
if (root == NULL) {
return;
}
struct TreeNode* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;
queue[++rear] = root;
while (front != rear) {
struct TreeNode* current = queue[++front];
printf("%d ", current->data);
if (current->left) {
queue[++rear] = current->left;
}
if (current->right) {
queue[++rear] = current->right;
}
}
printf("\n");
}
int main() {
struct TreeNode* root = NULL;
int choice, data;
while (1) {
printf("\nBinary Tree Operations:\n");
printf("1. Create\n");
printf("2. Insert\n");
printf("3. Inorder Traversal\n");
printf("4. Preorder Traversal\n");
printf("5. Postorder Traversal\n");
printf("6. Levelorder Traversal\n");
printf("7. Mirror Image\n");
printf("8. Height\n");
printf("9. Leaf Node display\n");
printf("10. Counting number of Nodes\n");
printf("11. Exit\n");
printf("Enter your choice: ");
scanf("%d", &choice);
switch (choice) {
case 1:
printf("Enter the data to insert: ");
scanf("%d", &data);
root = insert_node(root, data);
break;
case 2:
printf("Enter the data to insert: ");
scanf("%d", &data);
root = insert_node(root, data);
break;
case 3:
printf("Inorder Traversal: ");
inorder_traversal(root);
printf("\n");
break;
case 4:
printf("Preorder Traversal: ");
preorder_traversal(root);
printf("\n");
break;
case 5:
printf("Postorder Traversal: ");
postorder_traversal(root);
printf("\n");
break;
case 6:
printf("Level Order Traversal: ");
level_order_traversal(root);
printf("\n");
break;
case 7:
level_order_traversal(root);
mirror_image(root);
printf("Mirror Image: \n");
level_order_traversal(root);
break;
case 8:
printf("Height of Tree: %d\n", get_height(root));
break;
case 9:
printf("Leaf Nodes: ");
print_leaf_nodes(root);
printf("\n");
break;
case 10:
printf("Number of Nodes in the Tree: %d\n",
count_nodes(root));
break;
case 11:
exit(0);
default:
printf("Invalid choice. Please try again.\n");
}
}
return 0;
}