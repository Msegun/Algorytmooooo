#include <stdio.h>
#include <stdlib.h>

typedef struct Drzewo{
  int liczba;
  struct Drzewo *lewy;
  struct Drzewo *prawy;
}Tree;

Tree* WSTAW(Tree **korzen, int data);
void DRUKUJ(Tree *korzen);
Tree* SZUKAJ(Tree *korzen, int wartosc);
Tree* Minimum(Tree *korzen);
Tree* USUN(Tree *korzen, int wartosc);
int main(){
  Tree *drzewo;
  drzewo = NULL;

  WSTAW(&drzewo, 5);
  WSTAW(&drzewo, 3);
  WSTAW(&drzewo, 2);
  WSTAW(&drzewo, 8);
  WSTAW(&drzewo, 4);
  DRUKUJ(drzewo);

  if(SZUKAJ(drzewo, 8) == NULL){
    printf("\nNie znalazłem tej wartosci\n\n");
  }else{
    printf("\nZnalazłem poszukiwana wartosci\n");
  }
  USUN(drzewo, 3);
  printf("Drzewo po usunieciu 3\n");
  DRUKUJ(drzewo);
  WSTAW(&drzewo, 3);
  USUN(drzewo, 5);
  printf("\nDrzewo po usunieciu 5\n");
  DRUKUJ(drzewo);
  return 0;
}

Tree* WSTAW(Tree **korzen, int data){
  if(*korzen==NULL){
    *korzen = (Tree *)malloc(sizeof(Tree));
    (*korzen)->lewy = NULL;
    (*korzen)->prawy = NULL;
    (*korzen)->liczba = data;
  }
  else if(data < (*korzen)->liczba){
    (*korzen)->lewy = WSTAW(&(*korzen)->lewy, data);
  }
  else{
    (*korzen)->prawy = WSTAW(&(*korzen)->prawy, data);
  }
  return *korzen;
}

void DRUKUJ(Tree *korzen){
  if(korzen != NULL){
    DRUKUJ(korzen->lewy);
    printf("%d ", korzen->liczba);
    DRUKUJ(korzen->prawy);
  }
}

Tree* SZUKAJ(Tree *korzen, int wartosc){
  if(korzen == NULL){
    return NULL;
  }
  if(korzen->liczba == wartosc){
    return korzen;
  }
  if(korzen->liczba > wartosc){
    return SZUKAJ(korzen->lewy, wartosc);
  }
  return SZUKAJ(korzen->prawy, wartosc);
}

Tree* Minimum(Tree *korzen){
  if(korzen == NULL){
    return korzen;
  }
  if(korzen->lewy == NULL){
    return korzen;
  }
  return Minimum(korzen->lewy);
}

Tree* USUN(Tree *korzen, int wartosc){
  Tree* temp;
  if(korzen == NULL){
    return korzen;
  }
  if(wartosc < korzen->liczba){
    korzen->lewy = USUN(korzen->lewy, wartosc);
  }
  else{
    if(wartosc > korzen->liczba){
      korzen->prawy = USUN(korzen->prawy, wartosc);
    } else{
      if(korzen->prawy != NULL && korzen->lewy != NULL){
        temp = Minimum(korzen->prawy);
        korzen->liczba = temp->liczba;
        korzen->prawy = USUN(korzen->prawy, korzen->liczba);
      } else{
        temp = korzen;
        if(korzen->lewy == NULL){
          korzen = korzen->prawy;
        } else{
          if(korzen->prawy == NULL){
            korzen = korzen->lewy;
          }
          free(temp);
        }
      }
    }
  }
}
