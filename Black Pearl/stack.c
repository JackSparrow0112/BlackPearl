
//Infix to prefix

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

typedef struct {
    char items[MAX_SIZE];
    int top;
} Stack;

void initialize(Stack* stack) {
    stack->top = -1;
}

void push(Stack* stack, char item) {
    if (stack->top == MAX_SIZE - 1) {
        printf("Stack overflow\n");
        exit(1);
    }
    stack->items[++stack->top] = item;
}

char pop(Stack* stack) {
    if (stack->top == -1) {
        printf("Stack underflow\n");
        exit(1);
    }
    return stack->items[stack->top--];
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int precedence(char c) {
    if (c == '+' || c == '-')
        return 1;
    else if (c == '*' || c == '/')
        return 2;
    return 0;
}

void reverseString(char* str) {
    int length = strlen(str);
    int i, j;
    for (i = 0, j = length - 1; i < j; i++, j--) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

void infixToPrefix(char* infix, char* prefix) {
    Stack stack;
    initialize(&stack);
    int i, j;
    j = 0;

    reverseString(infix);

    for (i = 0; infix[i] != '\0'; i++) {
        char token = infix[i];

        if (isalnum(token)) {
            prefix[j++] = token;
        } else if (token == ')') {
            push(&stack, token);
        } else if (token == '(') {
            while (stack.top != -1 && stack.items[stack.top] != ')') {
                prefix[j++] = pop(&stack);
            }
            if (stack.top != -1 && stack.items[stack.top] != ')') {
                printf("Invalid expression\n");
                exit(1);
            } else {
                pop(&stack); // Pop the corresponding ')'
            }
        } else if (isOperator(token)) {
            while (stack.top != -1 && precedence(token) <= precedence(stack.items[stack.top])) {
                prefix[j++] = pop(&stack);
            }
            push(&stack, token);
        }
    }

    while (stack.top != -1) {
        prefix[j++] = pop(&stack);
    }

    prefix[j] = '\0';
    reverseString(prefix);
}

int main() {
    char infix[100], prefix[100];

    // Input infix expression
    printf("Enter an infix expression: ");
    scanf("%s", infix);

    // Convert infix to prefix
    infixToPrefix(infix, prefix);
    printf("Prefix expression: %s\n", prefix);

    return 0;
}









//infix to postfix
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define stack structure
#define MAX_SIZE 100
typedef struct {
    char items[MAX_SIZE];
    int top;
} Stack;

// Function to initialize the stack
void initialize(Stack* stack) {
    stack->top = -1;
}

// Function to push an item onto the stack
void push(Stack* stack, char item) {
    if (stack->top == MAX_SIZE - 1) {
        printf("Stack overflow\n");
        exit(1);
    }
    stack->items[++stack->top] = item;
}

// Function to pop an item from the stack
char pop(Stack* stack) {
    if (stack->top == -1) {
        printf("Stack underflow\n");
        exit(1);
    }
    return stack->items[stack->top--];
}

// Function to check if a character is an operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to return the precedence of an operator
int precedence(char c) {
    if (c == '+' || c == '-')
        return 1;
    else if (c == '*' || c == '/')
        return 2;
    return 0;
}

// Function to convert infix expression to postfix
void infixToPostfix(char* infix, char* postfix) {
    Stack stack;
    initialize(&stack);
    int i, j;
    j = 0;
    for (i = 0; infix[i] != '\0'; i++) {
        char token = infix[i];
        if (isalnum(token)) {
            postfix[j++] = token;
        } else if (token == '(') {
            push(&stack, token);
        } else if (token == ')') {
            while (stack.top != -1 && stack.items[stack.top] != '(') {
                postfix[j++] = pop(&stack);
            }
            if (stack.top != -1 && stack.items[stack.top] != '(') {
                printf("Invalid expression\n");
                exit(1);
            } else {
                pop(&stack);
            }
        } else if (isOperator(token)) {
            while (stack.top != -1 && precedence(token) <= precedence(stack.items[stack.top])) {
                postfix[j++] = pop(&stack);
            }
            push(&stack, token);
        }
    }
    while (stack.top != -1) {
        postfix[j++] = pop(&stack);
    }
    postfix[j] = '\0';
}

// Function to evaluate a postfix expression
int evaluatePostfix(char* postfix) {
    Stack stack;
    initialize(&stack);
    int i;
    for (i = 0; postfix[i] != '\0'; i++) {
        char token = postfix[i];
        if (isdigit(token)) {
            push(&stack, token - '0');
        } else if (isOperator(token)) {
            int operand2 = pop(&stack);
            int operand1 = pop(&stack);
            switch (token) {
                case '+':
                    push(&stack, operand1 + operand2);
                    break;
                case '-':
                    push(&stack, operand1 - operand2);
                    break;
                case '*':
                    push(&stack, operand1 * operand2);
                    break;
                case '/':
                    push(&stack, operand1 / operand2);
                    break;
            }
        }
    }
    return pop(&stack);
}

int main() {
    char infix[100], postfix[100];
    
    // Input infix expression
    printf("Enter an infix expression: ");
    scanf("%s", infix);
    
    // Convert infix to postfix
    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);
    
    // Evaluate the postfix expression
    int result = evaluatePostfix(postfix);
    printf("Result: %d\n", result);

    return 0;
}
