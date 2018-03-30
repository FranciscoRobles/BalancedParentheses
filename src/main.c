#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct StackNode {
    char data;
    struct StackNode* node;
};

struct StackNode* newNode(char c){
    struct StackNode* root = (struct StackNode*) malloc(sizeof(struct StackNode));
    (*root).data = c;
    (*root).node = NULL;
    return root;
}

int isEmpty(struct StackNode *root){
    return !root;
}

void push(struct StackNode** root, char c){
    struct StackNode* node = newNode(c);
    (*node).node = *root;
    *root = node;
}

int pop(struct StackNode** root){
    if(isEmpty(*root))
    {
        return 0;
    }
    struct StackNode* temporal = *root;
    *root = (*root)->node;
    free(temporal);
    return 1;
}

char top(struct StackNode* root){
    if(isEmpty(root))
    {
        return 'x';
    }
    return (*root).data;
}

int analizis(struct StackNode** root, char c){
    if(top(*root) == '{' && c == '}')
    {
        pop(root);
        printf("New top: %c\n", top(*root));
        return 1;
    }
    else if(top(*root) == '[' && c == ']')
    {
        pop(root);
        printf("New top: %c\n", top(*root));
        return 1;
    }
    else if(top(*root) == '(' && c== ')')
    {
        pop(root);
        printf("New top: %c\n", top(*root));
        return 1;
    }
    else
    {
        return 0;
    }
}

int main(){
    struct StackNode* root = NULL;
    printf("Top vacio = %c\n", top(root));
    push(&root, '(');
    push(&root, '{');
    printf("Top element %c\n", top(root));
    printf("Análizis = %d\n", analizis(&root, '}'));
}