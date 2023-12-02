#include<stdio.h>
#include<stdlib.h>
struct stack{
    int top;
    int size;
    int *arr;
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

int main(){
    struct stack *s=(struct stack*) malloc(sizeof(struct stack));
    s->top=-1;
    s->size=10;
    s->arr=(int*) malloc((s->size)*sizeof(int));
    if(isFull(s)){
        printf("Stack is full");
    }
    else if(isEmpty(s)){
         printf("Stack is Empty");
    }
    return 0;
}