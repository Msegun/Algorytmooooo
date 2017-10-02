#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct List{
  char* slowo;
  struct List *next;
  struct List *prev;
}list;

list *lista1 = NULL;
list *lista2 = NULL;
list *lista3 = NULL;

void WSTAW(list **head, char* word);
void DRUKUJ(list *element);
list* SZUKAJ(list* head, char* word);
void USUN(list** head, char* word);
void SCAL(list** list1, list** list2, list** list3);
list* BEZPOWTORZEN(list* head);
void KASUJ(list* head);

int main(){

  WSTAW(&lista1, "Bzyl");
  WSTAW(&lista1, "Ratatata");
  WSTAW(&lista1, "Harambe");
  WSTAW(&lista1, "Luchadore");
  printf("Lista pierwsza : \n");
  DRUKUJ(lista1);
  WSTAW(&lista2, "Harambe");
  WSTAW(&lista2, "Maklowicz");
  WSTAW(&lista2, "szyszka");
  WSTAW(&lista2, "Harambe");
  printf("\nLista druga : \n");
  DRUKUJ(lista2);
  list* listaposzukaniu;// = (list*)malloc(sizeof(list));
  listaposzukaniu = SZUKAJ(lista1, "Harambe");
  printf("Lista od wskaznika na znaleziony element: \n");
  DRUKUJ(listaposzukaniu);
//  DRUKUJ(lista1);//dowod ze listy po szukaniu sie nie zmienily
//  DRUKUJ(lista2);
  USUN(&lista1, "Ratatata");
  printf("\nLista po skasowaniu 'Ratatata'\n");
  DRUKUJ(lista1);
  printf("\nScalamy liste1 i liste2 w liste3 : \n");
  SCAL(&lista1, &lista2, &lista3);
  DRUKUJ(lista3);
  printf("\nLista3 bez powtorzen :\n");
  list* bezpowto;
  bezpowto = BEZPOWTORZEN(lista3);
  DRUKUJ(bezpowto);
  KASUJ(lista3);
  DRUKUJ(lista3);
  free(lista3);
  free(lista2);
  free(lista1);
  return 0;
}

void WSTAW(list **head, char* word){

  list *nowy=(list *)malloc(sizeof(list));
  nowy->slowo = word;
  nowy->next = *head;
  nowy->prev = NULL;
  *head = nowy;
}

void DRUKUJ(list *element){
  while(element!=NULL){
  	  printf("%s ", element->slowo) ;
    	element=element->next;
    }
  printf("\n");
}

list* SZUKAJ(list* element, char* word){

  while(element!=NULL){
    if(element->slowo == word){
      printf("\nZnaleziono '%s' na liscie\n", word);
      return element;
    }
    element=element->next;
  }
  printf("\nElementu nie znaleziono na liscie\n");
  return NULL;
}

void USUN(list** head, char* word){

  list* pierwszy = *head;
  list* poprzedni;
  list* tmp = *head;

  while(tmp != NULL){

      if(tmp->slowo == word){

        if(tmp == *head){
          *head = tmp->next;
          return;
        }
        else{
          poprzedni->next = tmp->next;
          free(tmp);
          return;
        }
      }
      else{
        poprzedni=tmp;
        tmp = tmp->next;
      }
  }

}

void SCAL(list** list1, list** list2, list** list3){
  list *tmp;
  *list3 = *list1;//
  tmp = *list3;
  while(tmp->next != NULL){
    tmp=tmp->next;
  }
  tmp->next=*list2;
  (*list2)->prev = tmp;
}

list* BEZPOWTORZEN(list* head){
  list *element1, *element2, *duplikat, *adrespowrotny;
  adrespowrotny = head;
  element1 = head;
  //Sprawdzamy elementy jeden po drugim
  while(element1 != NULL && element1->next != NULL)
  {
    element2 = element1;
    //Porównujemy element z reszta elementow
    while(element2->next != NULL)
    {
      //Jesli kopia to ja kasujemy
      if(element1->slowo == element2->next->slowo)
      {
        duplikat = element2->next;
        element2->next = element2->next->next;
        free(duplikat);
      }
      else
      {
        element2 = element2->next;
      }
    }
    element1 = element1->next;
  }
  return adrespowrotny;
}

void KASUJ(list* head){
  list *prev;
	prev=head;
	head=head->next;

	while(head!=NULL){
		free(prev);
		prev=head;
		head=head->next;
	}
	free(prev);
	printf("Skasowano liste.\n");
}
