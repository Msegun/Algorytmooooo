#include<stdio.h>
#include<stdlib.h>

 struct treeRB{
     int key; // klucz
     char color; // kolor
     struct treeRB *left, *right, *parent; // powiązania
};

void DRUKUJ(struct treeRB *korzen){
  if(korzen != NULL){
    DRUKUJ(korzen->left);
    printf(" [%d %c] ", korzen->key, korzen->color);
    DRUKUJ(korzen->right);
  }
}

 void RR(struct treeRB **root, struct treeRB *A){

     struct treeRB *B=A->right, *p=A->parent;

     A->right = B->left;
     if(A->right) A->right->parent = A;

     B->left=A;
     B->parent=p;
     A->parent=B;

    if(p){
        if(p->left == A) p->left=B;
        else p->right=B;
    }
    else *root=B;
}

void LL(struct treeRB ** root, struct treeRB *A){

    struct treeRB *B=A->left, *p=A->parent;

    A->left=B->right;
    if(A->left) A->left->parent=A;

    B->right=A;
    B->parent=p;
    A->parent=B;

    if(p){
        if(p->left==A) p->left=B;
        else p->right = B;
    }
     else *root = B;
}


 void addRB(struct treeRB **root, int key){
// funkcja główna naszego dodawania
   struct treeRB *nowy_element,*p=NULL,*d,*x,*y;
   // dodawanie elementu tak jak do BST
    nowy_element = (struct treeRB*)malloc(sizeof(struct treeRB));
    nowy_element->left = nowy_element->right = nowy_element->parent = NULL;
    nowy_element->key = key;
    nowy_element->color = 'R';
    d=*root;
   if(d==NULL){
         nowy_element->parent=NULL;
         nowy_element->color='B';
         *root=nowy_element;
       }
      else{
         while(d!=NULL){
             if(d->key > key){
                   p=d;
                   d=d->left;
             }else if(d->key < key){
                    p=d;
                    d=d->right;
             }else break;
         }
         if(d==NULL){
             if(p->key>key) p->left=nowy_element;
             else p->right=nowy_element;
             nowy_element->parent=p;
         }
         //

         if(p && p->color=='R'){
      // jeżeli dodało element, a rodzic tego elementu jest czerwony

             x=nowy_element;
             while(x!=NULL){
        // pętla ponieważ pierwszy przypadek dopuszcza przejście na wyższy poziom drzewa

                   p=x->parent; // p-rodzic naszego x

                   if(p->parent!=NULL){
             // ustalamy który przypadek lustrzany zachodzi
                          if(p->parent->left==p) y=p->parent->right;
                          else if(p->parent->right==p) y=p->parent->left;
                   }else y=NULL;

                   if(y && y->color=='R' && p->color=='R'){ // I przypadek
                          p->color=y->color='B';
                          if(p->parent==*root) break;

                          p->parent->color='R';
                          if(p)x=p->parent;
                    }else{
                         if(p->parent != NULL && y==p->parent->right){
                 // I przypadek lustrzany
                                 if(p->color=='R'){
                                         if(p->right==x) RR(root,p); // II przypadek

                                         LL(root,p->parent); // III przypadek
                                         x->parent->color='B';
                                         x->parent->right->color='R';
                                 }

                          }else if(p->parent && y==p->parent->left){
                          // II przypadek lustrzany
                                  if(p->color=='R'){
                                         if(p->left==x) LL(root,p); // II przypadek

                                         RR(root,p->parent); // III przypadek
                                         x->parent->color='B';
                                         x->parent->left->color='R';
                                   }
                           }
                           break; // wyjście z pętli
                   }
               }
          }
      }
}


int main(){

	struct treeRB *root = NULL;
	addRB(&root, 1);
	addRB(&root, 2);
	addRB(&root, 3);
	addRB(&root, 4);
	addRB(&root, 5);
	addRB(&root, 6);
  DRUKUJ(root);
	return 0;
}
