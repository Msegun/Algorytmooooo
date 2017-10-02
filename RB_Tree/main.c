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
void WSTAW_BST(Node **n, int val);
void DRUKUJ(Node *n);
Node* SZUKAJ(Node *n, int val);
void LEFT_ROTATE(Node** n, Node* x);
void RIGHT_ROTATE(Node** n, Node* x);


int main(void) {
	WSTAW(&rootMain, 15);
	DRUKUJ(rootMain);
	return 0;
}

Node* createNode(int val) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->number = val;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->parent = NULL;
	newNode->color = 'R';
	return newNode;
}

void WSTAW_BST(Node **n, int val) { //n == root, val == value we want to insert
    if((*n) == NULL) {
		Node* tmp = createNode(val);
		(*n) = tmp;
    } else {
    	if(val < (*n)->number) {
    		WSTAW_BST(&(*n)->left,val);
    		(*n)->left->parent = (*n);
    	}
    	if(val >= (*n)->number) {
    		WSTAW_BST(&(*n)->right,val);
    		(*n)->right->parent = (*n);
    	}
    }
}

void WSTAW(Node **n, int val) {

	Node* newNode = createNode(val);
	WSTAW_BST(&rootMain, val);
	/*Node* grandparent = NULL;
	Node* par = NULL;
	while(newNode != (*n) && newNode->parent->color == 'R') {
		grandparent = newNode->parent->parent;
		par = newNode->parent;
		if(par == grandparent->left) {
			Node* uncle = grandparent-> right;
			if(uncle->color == 'R' && uncle != NULL) {
				par->color = 'B';
				uncle->color = 'B';
				grandparent->color = 'R';
				newNode = grandparent;
			}
			else{
                if(newNode == par->right) {
                    LEFT_ROTATE(n, newNode);
                    newNode = par;
                    par = newNode->parent;
                }
                par->color = 'B';
                grandparent->color = 'R';
                RIGHT_ROTATE(n, grandparent);
            }
		}
        else{
            Node* uncle = grandparent-> left;
            if(uncle->color == 'R' && uncle != NULL) {
                par->color = 'B';
                uncle->color = 'B';
                grandparent->color = 'R';
                newNode = grandparent;
			} else {
			    if(newNode == par->left) {
                    RIGHT_ROTATE(n, newNode);
                    newNode = par;
                    par = newNode->parent;
                }
                par->color = 'B';
                grandparent->color = 'R';
                LEFT_ROTATE(n, grandparent);
            }
        }
	}*/
	(*n)->color = 'B';
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

void LEFT_ROTATE(Node** n, Node* x) {
	Node* y;
	y = x->right;
	x->right = y->left;
	if (y->left != NULL) {
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == NULL) {
		(*n) = y;
	}
	else if (x->number == x->parent->left->number) {
		x->parent->left = y;
	}
	else x->parent->right = y;
	y->left = x;
	x->parent = y;
	return;
}

void RIGHT_ROTATE(Node** n, Node* x) {
	Node* y;
	y = x->left;
	x->left = y->right;
	if (y->right != NULL) {
		y->right->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == NULL) {
		(*n) = y;
	}
	else if (x->number == x->parent->left->number) {
		x->parent->left = y;
	}
	else x->parent->right = y;
	y->right = x;
	x->parent = y;
	return;
}
