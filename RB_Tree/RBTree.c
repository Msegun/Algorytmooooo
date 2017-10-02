#include <stdio.h>
#include <stdlib.h>

//Jan Bienias
//238201
//Task nr.: 1
//https://inf.ug.edu.pl/~mdziemia/aisd/zad-czerwono-czarne.txt

//Sources :
//http://stackoverflow.com/questions/14253816/red-black-tree-implementation-in-c ->
//mainly to check if my implementation of Algorithm ...
// ... (from Thomas H. Cormen's book) was correct

typedef struct Tree {
  int number;
  char color; //B = black, R = red
  struct Tree *right;
  struct Tree *left;
  struct Tree *parent;
}Node;

Node* rootMain = NULL;

void WSTAW(Node **n, int val);
void WSTAW_FIX(Node *n, Node*z);
void LEFT_ROTATE(Node* n, Node* x);
void RIGHT_ROTATE(Node* n, Node* x);
void DRUKUJ(Node *n);
Node* SZUKAJ(Node *n, int val);

int main(void) {

	WSTAW(&rootMain, 2);
	WSTAW(&rootMain, 3);
	WSTAW(&rootMain, 10);
	WSTAW(&rootMain, 1);
	WSTAW(&rootMain, 2);
	WSTAW(&rootMain, 3);
	WSTAW(&rootMain, 10);
	WSTAW(&rootMain, 1);
	WSTAW(&rootMain, 2);
	WSTAW(&rootMain, 3);
	WSTAW(&rootMain, 10);
	WSTAW(&rootMain, 1);
	DRUKUJ(rootMain);
	return 0;
}

void WSTAW(Node **n, int val) { //n == root, val == value we want to insert

	if(val < 0) {
    	printf("You can't insert [%d] node, because it is lesser then zero!\n", val);
    	return;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));

    if(*n == NULL) {
    	newNode->number = val;
    	newNode->left = NULL;
    	newNode->right = NULL;
    	newNode->parent = *n;
    	*n = newNode;

    } else {
    	if(val < (*n)->number) {
    		WSTAW(&(*n)->left,val);
    	}
    	if(val > (*n)->number) {
    		WSTAW(&(*n)->right,val);
    	}
    }

    newNode->color = 'R';
    //WSTAW_FIX(n, newNode);

}

void WSTAW_FIX(Node *n, Node*z) { //n == root, z == element that is possibly incorrect in RB tree
	Node* y;
	while(z->parent->color == 'R') {
		if(z->parent->number == z->parent->parent->left->number) {
			y = z->parent->parent->right;
			if(y != NULL && y->color == 'R') {
				z->parent->color = 'B';
				y->color = 'B';
				z->parent->parent->color = 'R';
				z = z->parent->parent;
			}
			else if (z->number == z->parent->right->number) {
				z=z->parent;
				LEFT_ROTATE(n, z);
			}
			z->parent->color = 'B';
			z->parent->parent->color = 'R';
			RIGHT_ROTATE(n, z->parent->parent);
		}
		else { //same as above, change only : right -> left, left -> right (functions and variables)
			y= z->parent->parent->left;
			if(y != NULL && y->color == 'R') {
				z->parent->color = 'B';
				y->color = 'B';
				z->parent->parent->color = 'R';
				z = z->parent->parent;
			}
			else if (z->number == z->parent->left->number) {
				z=z->parent;
				RIGHT_ROTATE(n, z);
			}
			z->parent->color = 'B';
			z->parent->parent->color = 'R';
			LEFT_ROTATE(n, z->parent->parent);
		}
	}
}

void DRUKUJ(Node *n) //in-order printing
{
    if(n==NULL)
        return;
    DRUKUJ(n->left);
    if(n->color == 'R')
    	printf("[%d] \tRED\n", n->number);
    else if(n->color == 'B')
    	printf("[%d] \tBLACK\n", n->number);
    DRUKUJ(n->right);
}

Node* SZUKAJ(Node *n, int val) {

	if(n!=NULL)	{
        if(val == n->number) {
            printf("I've found [%d] node! Color: %c\n", n->number, n->color);
            return n;
        }
        else if(val > n->number)
            SZUKAJ(n->right, val);
        else if(val < n->number)
            SZUKAJ(n->left, val);
	} else
		printf("I didn't find [%d] node!\n", val);

	return NULL;
}

void LEFT_ROTATE(Node* n, Node* x) {
	Node* y;
	y = x->right;
	x->right = y->left;
	if (y->left != NULL) {
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == NULL) {
		n = y;
	}
	else if (x->number == x->parent->left->number) {
		x->parent->left = y;
	}
	else x->parent->right = y;
	y->left = x;
	x->parent = y;
	return;
}

void RIGHT_ROTATE(Node* n, Node* x) {
	Node* y;
	y = x->left;
	x->left = y->right;
	if (y->right != NULL) {
		y->right->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == NULL) {
		n = y;
	}
	else if (x->number == x->parent->left->number) {
		x->parent->left = y;
	}
	else x->parent->right = y;
	y->right = x;
	x->parent = y;
	return;
}

