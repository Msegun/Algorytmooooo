#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//https://github.com/okoniewskid/Algorytmy_i_struktury_danych/blob/master/listy%20dowiazaniowe/LISTA.c
//http://www.learn-c.org/en/Linked_lists

typedef struct Punkt{
	int x;
	struct Punkt* next;
	struct Punkt* prev;
}punkt;

punkt* L1 = NULL;

void WSTAW(punkt** L, int i)
{
    punkt* nowy = (punkt*)malloc(sizeof(punkt));
    nowy->x=i;
    nowy->next = *L;
    nowy->prev = NULL;
    *L = nowy;
}

void KASUJ(punkt** L)
{
    *L=NULL;
}

punkt* SZUKAJ(punkt* L, int i)
{
    if(L==NULL)
        printf("Ta lista jest pusta!\n");
    while(L != NULL)
    {
        if(L->x == i)
        {
            printf("Znalazlem [%d] na liscie :)!\n", i);
            return L;
        }
        L=L->next;
    }
    printf("Nie znalazlem [%d] na liscie :(!\n", i);
    return NULL;
}

void USUN(punkt** L, int i)
{
    if(L == NULL)
    {
        printf("Ta lista jest pusta!\n");
        return;
    }
    punkt* first = *L;
    punkt* prev;
    punkt* tmp = *L;
    while(tmp != NULL)
    {
        if(tmp->x == i)
        {
            if(tmp == *L)
            {
                *L=tmp->next;
                return;
            }

            else
            {
                prev->next = tmp->next;
                free(tmp);
                return;
            }
        }
        else
        {
            prev=tmp;
            tmp = tmp->next;
        }
    }
}

void DRUKUJ(punkt* L)
{
    if(L==NULL)
        printf("Ta lista jest pusta!\n");
    while(L != NULL)
    {
        printf("[%d]", L->x);
        L=L->next;
    }
}

int main()
{
    punkt* nowy = (punkt*)malloc(sizeof(punkt));
    WSTAW(&L1,1);
    WSTAW(&L1,1);
    WSTAW(&L1,1);
    WSTAW(&L1,4);
    DRUKUJ(L1);
    printf("\n");
    nowy = SZUKAJ(L1, 1);
    printf("nowy: ");
    DRUKUJ(nowy);
    printf("\n");
    WSTAW(&L1, 4);
    DRUKUJ(L1);
    printf("\n");
    USUN(&L1,4);
    USUN(&L1,1);
    DRUKUJ(L1);
    printf("\n");
    return 0;
}
