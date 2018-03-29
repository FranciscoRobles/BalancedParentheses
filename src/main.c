#include <stdio.h>
#include <stdlib.h>

struct StackNode {
    char c;
    struct StackNode* node;
};

struct StackNode* newNode(char c){
    StackNode* root = (StackNode) malloc(sizeof(StackNode));
    root.c = c;
    root.node = NULL;
    return root;
}

int isEmpty(StackNode* root){
    return !root;
}

void push(StackNode** root, char c){
    StackNode* node = newNode(c);
    node.node = *root;
    *root = node;
}

void pop(StackNode** root){
    if(isEmpty(*root))
    {
        break;
    }
    StackNode* temporal = *root;
    *root = (*root) node;
    free(temporal);
}