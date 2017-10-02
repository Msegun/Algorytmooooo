//Krzysztof Borawski 238152
//Drzewa czerwono czarne wersja bardzo łopatologiczna
//Zamierzam zrobic drugą wersję tego programu w JAVIE
//Żeby nie było uzywałem do pomocy ze zrobieniem projektu internetu

#include<stdio.h>
#include<stdlib.h>

struct RBTREE{
  int klucz;
  char kolor;
  struct RBTREE *lewy, *prawy, *ojciec;
};

void RR(struct RBTREE **root, struct RBTREE *A);
void LL(struct RBTREE **root, struct RBTREE *parent);
void DRUKUJ(struct RBTREE *korzen);
void WSTAW(struct RBTREE **root, int klucz);
int SZUKAJ(struct RBTREE *korzen, int wartosc);

int main(){

  struct RBTREE *root = NULL;
  WSTAW(&root, 1);
  WSTAW(&root, 2);
  WSTAW(&root, 3);
  WSTAW(&root, 4);
  WSTAW(&root, 5);
  WSTAW(&root, 6);
  WSTAW(&root, 8);
  WSTAW(&root, 7);
  DRUKUJ(root);
  if(SZUKAJ(root, 8) == 0){
    printf("\nNie znalazłem tej wartosci\n\n");
  }else{
    printf("\nZnalazłem poszukiwana wartosci\n");
  }
  if(SZUKAJ(root, 9) == 0){
    printf("\nNie znalazłem tej wartosci\n\n");
  }else{
    printf("\nZnalazłem poszukiwana wartosci\n");
  }
  return 0;
}

void DRUKUJ(struct RBTREE *korzen){
  if(korzen != NULL){
    DRUKUJ(korzen->lewy);
    printf(" [%d %c] ", korzen->klucz, korzen->kolor);
    DRUKUJ(korzen->prawy);
  }
}

int SZUKAJ(struct RBTREE *korzen, int wartosc){
  if(korzen == NULL){
    return 0;
  }
  if(korzen->klucz == wartosc){
    return 1;
  }
  if(korzen->klucz > wartosc){
    return SZUKAJ(korzen->lewy, wartosc);
  }
  return SZUKAJ(korzen->prawy, wartosc);
}

void RR(struct RBTREE **root, struct RBTREE *parent){

    struct RBTREE *temp=parent->prawy, *p=parent->ojciec;

    parent->prawy = temp->lewy;
    if(parent->prawy) parent->prawy->ojciec = parent;

    temp->lewy=parent;
    temp->ojciec=p;
    parent->ojciec=temp;

   if(p!= NULL){
       if(p->lewy == parent) p->lewy=temp;
       else p->prawy=temp;
   }
   else *root=temp;
}

void LL(struct RBTREE **root, struct RBTREE *parent){
    //p ojciec temp
    struct RBTREE *temp=parent->lewy, *p=parent->ojciec;

    parent->lewy=temp->prawy;
    if(parent->lewy)
      parent->lewy->ojciec=parent;

    temp->prawy=parent;
    temp->ojciec=p;
    parent->ojciec=temp;

    if(p!=NULL){
        if(p->lewy==parent) p->lewy=temp;
        else p->ojciec = temp;
    }
     else *root = temp;
}

void WSTAW(struct RBTREE **root, int klucz)
{
//Ustalanie zmiennych potrzebnych
  struct RBTREE *new, *parent = NULL, *d, *x, *y;
  new = (struct RBTREE*)malloc(sizeof(struct RBTREE));
//Przygotowanie nowego elementu
  new->lewy = NULL;
  new->prawy = NULL;
  new->ojciec = NULL;
  new->klucz = klucz;
  new->kolor = 'R';
  d=*root;
//Jak drzewo jest puste
  if(d == NULL)
  {
    new->ojciec = NULL;
    new->kolor = 'B';
    *root = new;
  }
  else
  {
    while(d!=NULL)//Petla by dotrzec na spód drzewa
    {
      if(d->klucz > klucz)
      {
        parent=d;
        d=d->lewy;
      }
      else
        if(d->klucz < klucz)
        {
          parent=d;
          d=d->prawy;
        }
    }

    if(d==NULL)//Ustawienie ojca i wstawienie elementu
    {
      if(parent->klucz > klucz)
        parent->lewy = new;
      else parent->prawy = new;
      new->ojciec = parent;
    }

    //Rodzic dodanego elementu jest czerwony
    if(parent!=NULL && parent->kolor=='R')
    {
      x=new;
      while(x!=NULL)
      {
        parent=x->ojciec; //rodzic x
        //wujkowie
        if(parent->ojciec!=NULL)
        {
          if(parent->ojciec->lewy == parent)
            y=parent->ojciec->prawy;
          else
            if(parent->ojciec->prawy == parent)
              y=parent->ojciec->lewy;
        }else y=NULL;
              // I przypadek
          if(y != NULL && y->kolor=='R' && parent->kolor=='R')
            {
              parent->kolor='B';
              y->kolor='B';
              if(parent->ojciec==*root)
                break;
              parent->ojciec->kolor='R';
              if(parent!=NULL)
              x=parent->ojciec;
            }
            else
            {//Przypadki inne
              if(parent->ojciec != NULL && y==parent->ojciec->prawy)
              {
                if(parent->kolor=='R')
                {
                  if(parent->prawy==x)
                    RR(root,parent); // II przypadek
                  LL(root,parent->ojciec); // III przypadek
                  x->ojciec->kolor='B';
                  x->ojciec->prawy->kolor='R';
                }
              }
              else
                if(parent->ojciec != NULL && y==parent->ojciec->lewy)
                {
                  if(parent->kolor=='R')
                  {
                    if(parent->lewy==x)
                      LL(root,parent); // II przypadek
                    RR(root,parent->ojciec); // III przypadek
                    x->ojciec->kolor='B';
                    x->ojciec->lewy->kolor='R';
                  }
                }
                break; // wyjście z pętli
              }
          }
     }
 }
}
