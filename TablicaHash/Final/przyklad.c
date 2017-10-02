#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Informacje{
  int liczba;
  char *nazwisko;
}Inf;

void reset_tab(Inf tab[], int rozmiar);
int HashInsert(Inf tab[], int rozmiar, char *nazwisko);
int to_string(char *nazwisko);
int Hash(int k, int i, int rozmiar);
void PrintTab(Inf tab[], int rozmiar);

int main(){

  int rozmiar = 10;
  Inf tab[rozmiar];

  reset_tab(tab, rozmiar);
  HashInsert(tab, rozmiar, "Kamyczek");
  HashInsert(tab, rozmiar, "Kowalski");
  HashInsert(tab, rozmiar, "Kamyczek");
  HashInsert(tab, rozmiar, "Kowalski");
  HashInsert(tab, rozmiar, "Kowalski");
  HashInsert(tab, rozmiar, "Kowalski");//doda go na poczatek
  HashInsert(tab, rozmiar, "Bienias");
  PrintTab(tab, rozmiar);

  return 0;
}

void PrintTab(Inf tab[], int rozmiar){
  int i = 0;
  for(i = 0; i < rozmiar; i++){
    printf("%d. %s\n", tab[i].liczba, tab[i].nazwisko);
  }
}

int Hash(int k, int i, int rozmiar){
  int suma;
  k = k%rozmiar;
  suma = (k+i)%rozmiar;
  return suma;
}

int to_string(char *nazwisko){
  int i;
  int suma = 0;
  int x = 1;
  for(i = 0; i < strlen(nazwisko); i++){
    if((int)nazwisko[i] != 32)
      suma = suma * x + (int)nazwisko[i];
  }
  return suma;
}

int HashInsert(Inf tab[], int rozmiar, char *nazwisko){
  //Wartosc NIL w tab == 0
  //Wartosc DEL po skasowaniu w tab == -1
  int i, j;
  int x;
  x = to_string(nazwisko);
  i = 0;
  do{
    j = Hash(x, i, rozmiar);
    if(tab[j].liczba == 0 || tab[j].liczba == -1){
      tab[j].nazwisko = nazwisko;
      tab[j].liczba = x;
      return j;
    }
    i++;
  }while(i < rozmiar);

  return 0;
}

void reset_tab(Inf tab[], int rozmiar){
  int i;
  for(i = 0; i < rozmiar; i++){
    tab[i].liczba = 0;
    tab[i].nazwisko = NULL;
  }
}
