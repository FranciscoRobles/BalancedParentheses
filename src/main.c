#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

FILE *inicio, *avance;
char palabra[100];

//Stack
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

//Lectura de archivo
void aceptar(){
	long inicioPalabra = ftell(inicio);
	long finPalabra = ftell(avance);

	fread(palabra, finPalabra - inicioPalabra, 1, inicio);

	fseek(inicio, finPalabra, SEEK_SET);
}

void rechazar(){
	fseek(avance, ftell(inicio), SEEK_SET);
}

char obtenerCaracter(){
	return fgetc(avance);
}

int isfeof(){
	char c = obtenerCaracter();
	rechazar();
	return c == EOF;
}


int analizis(struct StackNode** root){
	int i = 0;
	char c = obtenerCaracter();
	while(c != ' ' && c != '\t' && c != '\n' && c != EOF)
	{
		if( c == '(' || c == '[' || c == '{')
		{
			push(root, c);
			printf("Push: %c\n", c);
			return 0;
		}
		else
		{
			if(c == ')'|| c == ']'|| c== '}')
			{
				if(top(*root) == '{' && c == '}')
				{
					pop(root);
					printf("Popped with: %c\n", c);
					if(top(*root) == 'x')
					{
						printf("Stack is empty.\n");
					}
					else
					{
						printf("New top: %c\n", top(*root));
					}
					return 0;
				}
				else if(top(*root) == '[' && c == ']')
				{
					pop(root);
					printf("Popped with: %c\n", c);
					if(top(*root) == 'x')
					{
						printf("Stack is empty.\n");
					}
					else
					{
						printf("New top: %c\n", top(*root));
					}
					return 0;
				}
				else if(top(*root) == '(' && c== ')')
				{
					pop(root);
					printf("Popped with: %c\n", c);
					if(top(*root) == 'x')
					{
						printf("Stack is empty.\n");
					}
					else
					{
						printf("New top: %c\n", top(*root));
					}
					return 0;
				}
				else
				{
					if(i > 0)
					{
						printf("There is an error with the brackets.\n");
						return -1;
					}
					printf("There is an error with the brackets.\n");
					return -1;
				}
			}
		}
		c = obtenerCaracter();
		i++;
	}
	return 0;
}

int main(){
	struct StackNode* root = NULL;
	int x = 0;
	inicio = fopen("brackets.txt", "r");
	avance = fopen("brackets.txt", "r");
	while(!isfeof())
	{
		x = analizis(&root);
		if(x == -1)
		{
			break;
		}
		for(int i = 0; i<100;i++)
		{
			aceptar();
			palabra[i] = (char)0;
		}
	}
	if(!isEmpty(root) || x == -1)
	{
		printf("Not balanced brackets\n");
	}
	else
	{
		printf("The stack is empty, so it is balanced\n");
	}
	fclose(inicio);
	fclose(avance);
	/*
	printf("Top vacio = %c\n", top(root));
	push(&root, '(');
	push(&root, '{');
	printf("Top element %c\n", top(root));
	printf("Análizis = %d\n", analizis(&root, '}'));
	*/
}