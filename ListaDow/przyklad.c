#include <stdio.h>
#include <stdlib.h>

typedef struct Punkt{
	int x;
	int y;
	struct Punkt *prev;
	struct Punkt *next;
}punkt;

	punkt *lista1 = NULL;
	punkt *lista2 = NULL;

//Wyswietlanie listy
void DRUKUJ(punkt *element){
	while(element->next!=NULL){
    	//printf("(%d,%d) \n", element->x, element->y) ;
    	element=element->next;
	}
	while(element!=NULL){
    	printf("(%d,%d) \n", element->x, element->y) ;
    	element=element->prev;
	}
}
//Wstawianie elementu
void WSTAW(punkt **Pierwszy, int i, int j){
	punkt *nowy=(punkt *)malloc(sizeof(punkt));
	punkt *temp;
	temp = *Pierwszy;
	nowy->x=i;
	nowy->y=j;
	nowy->next=*Pierwszy;
	nowy->prev=NULL;
	if(nowy->next!=NULL)temp->prev=nowy;
	*Pierwszy=nowy;
}
//Usuwanie elementu
void USUN(punkt *element, int i, int j){
	punkt *prev,*next;
	while(element->next!=NULL && element->x!=i && element->y!=j){
	prev=element;
	element=element->next;
	}
	if(element->next==NULL){
		element=NULL;
	}
	else{
		prev->next=element->next;
		next=element->next;
		next->prev=element->prev;
		free(element);
	}
}
//Szukanie elementu
void SZUKAJ(punkt *element, int i, int j){
	while(element!=NULL){
		if(element->x==i && element->y==j){
			printf("Znaleziono element (%d,%d) na liscie.\n",i,j);
			return;
		}
		element=element->next;
	}
	printf("Nie znaleziono elementu (%d,%d) na liscie.\n",i,j);
}
//Kasowanie listy
void KASUJ(punkt *nowy){
	punkt *prev;
	prev=nowy;
	nowy=nowy->next;

	while(nowy!=NULL){
		free(prev);
		prev=nowy;
		nowy=nowy->next;
	}
	free(prev);
	printf("Skasowano liste.\n");
}
//Scalanie listy
void SCAL(punkt **temp,punkt **temp2){
	punkt *tmp ;
	tmp=*temp;
	while(tmp->next!=NULL){
		tmp=tmp->next;
	}
	tmp->next=*temp2;
	(*temp2)->prev=tmp;
}

int main(){
	WSTAW(&lista1,2,1);
	WSTAW(&lista1,3,8);
	WSTAW(&lista1,6,5);

	WSTAW(&lista2,1,5);
	WSTAW(&lista2,8,9);
	WSTAW(&lista2,7,3);

	printf("Lista 1.\n");
	DRUKUJ(lista1);
	printf("Lista 2.\n");
	DRUKUJ(lista2);

	SZUKAJ(lista1,8,9);
	SZUKAJ(lista2,8,9);

	USUN(lista1,3,8);

	DRUKUJ(lista1);
	printf("Po scaleniu list.\n");
	SCAL(&lista1,&lista2);
	DRUKUJ(lista1);

	KASUJ(lista2);
	return 0;
}
