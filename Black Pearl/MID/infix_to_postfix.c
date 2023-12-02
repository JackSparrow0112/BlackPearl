

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct stack{
    int top;
    int size;
    char *arr;
};

int isFull(struct stack *s){
    if(s->top==s->size-1){
        return 1;
    }
    else{
        return 0;
    }
}
int isEmpty(struct stack *s){
    if(s->top==-1){
        return 1;
    }
    else{
        return 0;
    }
}
void push(struct stack *s,char data){
    if(isFull(s)){
       printf("Stack is full\n");  
    }
    else{
    s->top++;
    s->arr[s->top]=data;
    }
}


char pop(struct stack *s){
  if(isEmpty(s)){
        printf("Stack is empty\n");
        return -1;
    }
    else{
        char value = s->arr[s->top];
        s->top--;
        return value;
    }
}


int isOperator(char ch){
    if(ch=='+'||ch=='-'||ch=='*'||ch=='/'){
        return 1;
    }
       return 0;
}

int precedence(char ch){
    if(ch=='*'||ch=='/'){
        return 3;
    }
    if(ch=='+'||ch=='-'){
        return 2;
    }
    else{
        return 0;
    }
}

int stackTop(struct stack *s){
    return s->arr[s->top];
}

char *infixToPostfix(char *infix){
    struct stack *s =(struct stack*)malloc(sizeof(struct stack));
    s->top=-1;
    s->size=50;
    s->arr=(char*)malloc((s->size)*sizeof(char));
    char *postfix=(char*)malloc((strlen(infix)+1)*sizeof(char));
    int i=0;//track the infix
    int j=0;//track post fix addition
    while(infix[i]!='\0'){
    if(!isOperator(infix[i])){
        postfix[j]=infix[i];
        i++;j++;
    }
    else{
        if(precedence(infix[i])>precedence(stackTop(s))){
            push(s,infix[i]);
            i++;
        }
        else{
            postfix[j]=pop(s);
            j++;
        }
    }
    }
    while(!isEmpty(s)){
    postfix[j]=pop(s);
    j++;
    }
    postfix[j]='\0';
    return postfix;
}





int main(){
   char *infix ="x-y/z-k*d";
   printf("postfix is %s",infixToPostfix(infix));
    return 0;
}