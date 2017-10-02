#include <stdio.h>
#include <stdlib.h>

struct rbtNode{
int key;
char color;
struct rbtNode *left;
struct rbtNode *right;
struct rbtNode *parent;
};

struct rbtNode* root = NULL;

void leftRotate(struct rbtNode *root,struct rbtNode *x){
struct rbtNode *y;
y = x->right;  //Set y
x->right = y->left; // Turn y's left subtree into x's right subtree
if( y->left != NULL){
    y->left->parent = x; //Bridge the y's left sublink
}
y->parent = x->parent; //Bridge x's old parent and y's parent
if( x->parent == NULL){
    root = y;
}
else if( x->key == x->parent->left->key){
    x->parent->left = y; //Bridge x's old parent's left or right child
}
else x->parent->right = y;
y->left = x; //put x on y's left
x->parent = y; //Take care of x's parent

return;
}

void rightRotate(struct rbtNode *root,struct rbtNode *y){
struct rbtNode *x;
x = y->left; //set x
y->left = x->right; //Turn x's right subtree into y's left subtree
if ( x->right != NULL){
    x->right->parent = y;
}
x->parent = y->parent; //Bridge y's old parent and x's parent
if( y->parent == NULL){
    root = x;
} 
else if( y->key == y->parent->left->key){
    y->parent->left = x; //Bridge y's old parent's left or right child
}
else y->parent->right = x;
x->right = y; //put y on x's right
y->parent = x; //Take care of y's parent

return;

}

void rbInsertFix(struct rbtNode *root,struct rbtNode *z){
struct rbtNode *y;
while (z->parent->color == 'r'){
    if (z->parent->key == z->parent->parent->left->key){
        y = z->parent->parent->right;
        if (y->color == 'r'){
            z->parent->color = 'b';
            y->color = 'b';
            z->parent->parent->color = 'r';
            z = z->parent->parent;
        }
        else if (z->key == z->parent->right->key){
            z = z->parent;
            leftRotate(root,z);
        }
        z->parent->color = 'b';
        z->parent->parent->color = 'r';
        rightRotate(root,z->parent->parent);
    }
    else {
        y = z->parent->parent->left;
        if (y->color == 'r'){
            z->parent->color = 'b';
            y->color = 'b';
            z->parent->parent->color = 'r';
            z = z->parent->parent;
        }
        else if (z->key == z->parent->left->key){
            z = z->parent;
            rightRotate(root,z);
        }
        z->parent->color = 'b';
        z->parent->parent->color = 'r';
        leftRotate(root,z->parent->parent);
    }
}
root->color = 'b';
}

void rbInsert(int val){
struct rbtNode *z = (struct rbtNode*)malloc(sizeof(struct rbtNode));
z->key = val;
z->left = NULL;
z->right = NULL;
z->color = 'r';
struct rbtNode *x = root;
struct rbtNode *y;
if ( root == NULL ){
    root = z;
    root->color = 'b';
    return;
}
while ( x != NULL){
    y = x;
    if ( z->key < x->key){
        x = x->left;
    }
    else x = x->right;
}
z->parent = y;
if ( y == NULL){
    root = z;
}
else if( z->key < y->key ){
    y->left = z;
}
else y->right = z;
rbInsertFix(root,z);

return;
}

/*Display RBT - Inorder Traversal*/
void inorderTree(struct rbtNode* root){
struct rbtNode* temp = root;
if (temp != NULL){
    inorderTree(temp->left);
    printf(" %d-%c ",temp->key,temp->color);
    inorderTree(temp->right);
}
return;
}

int main(int argc, char* argv[]){
int loop = 1;
while(loop){
    printf("\nRed Black Tree Management - Enter your choice : ");
    printf("\n1\tInsert into RBT\n2\tDisplay RBT inorder\n");
    int choice;
    int val;
    scanf("%d",&choice);
    switch(choice){
        case 1:
        printf("\nEnter the integer you want to add : ");
        scanf("%d",&val);
        rbInsert(val);
        break;

        case 2:
        printf("\nInorder tree traversal left-root-right\n");
        inorderTree(root);
        break;

        default:
        printf("\nInvalid Choice\n");
    }
    printf("\nPress '0' to terminate and '1' to continue : ");
    scanf("%d",&loop);
}

return 0;
}
