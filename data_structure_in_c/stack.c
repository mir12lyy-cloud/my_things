#include<stdio.h>
#include<stdlib.h>

#define NORMAL_STACK_SIZE 10
#define IS_NOT_EXISTED -2

typedef struct{
    int *data;
    int top;
    size_t capacity;
}stack;

stack creatIntStack(size_t capacity){
    stack returnStack;
    if(capacity > 0) returnStack.capacity = capacity;
    else returnStack.capacity = NORMAL_STACK_SIZE;
    returnStack.top = -1;
    returnStack.data = (int*)malloc(returnStack.capacity * sizeof(int));
    if(returnStack.data == NULL){
        returnStack.top = IS_NOT_EXISTED;
    }
    return returnStack;
}

void destoryStack(stack *astack){
    if(astack -> top == IS_NOT_EXISTED){
        printf("This stack is not existed.\n");
        return;
    }
    astack -> top = IS_NOT_EXISTED;
    free(astack -> data);
    astack -> data = NULL;
}

int isStackEmpty(stack *astack){
    if(astack -> top == IS_NOT_EXISTED){
        printf("This stack is not existed.\n");
        return -1;
    }
    return astack -> top == -1;
}

int isStackFull(stack *astack){
    if(astack -> top == IS_NOT_EXISTED){
        printf("This stack is not existed.\n");
        return -1;
    }
    return astack -> top == (astack -> capacity) - 1;
}

void push(stack *astack, int num){
    if(astack -> top == IS_NOT_EXISTED){
        printf("This stack is not existed.\n");
        return;
    }
    if(isStackFull(astack)){
        printf("overflow!\n");
        return;
    }
    astack -> top += 1;
    astack -> data[astack -> top] = num;
}

void pop(stack *astack){
    if(astack -> top == IS_NOT_EXISTED){
        printf("This stack is not existed.\n");
        return;
    }
    if(isStackEmpty(astack)){
        printf("Empty!\n");
        return;
    }
    astack -> top -= 1;
}

int peek(stack *astack){
    if(astack -> top == IS_NOT_EXISTED){
        printf("This stack is not existed.\n");
        return -1;
    }
    if(isStackEmpty(astack)){
        printf("Empty!\n");
        return -1;
    }
    return astack -> data[astack -> top];
}

int main(){
    stack myStack;
    myStack = creatIntStack(10);
    printf("isEmpty? = %d\n", isStackEmpty(&myStack));
    push(&myStack, 3);
    printf("Top is %d\n", peek(&myStack));
    push(&myStack, 4);
    printf("Top is %d\n", peek(&myStack));
    pop(&myStack);
    printf("Top is %d\n", peek(&myStack));
    destoryStack(&myStack);
    push(&myStack, 1);
    return 0;
}