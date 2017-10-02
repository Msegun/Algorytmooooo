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
int licz_linie();
void czytanie_z_pliku(char **tab, int ilosc_linii);
int ile_niepustych(Inf tab[], int rozmiar);
void kasujpol(Inf tab[], int rozmiar);
int CountDEL(Inf tab[], int rozmiar);

int main(){
/*
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
  PrintTab(tab, rozmiar); */

  int ilosc_linii;
  ilosc_linii = licz_linie();
  char **TablicaWString;
  TablicaWString = (char**) malloc(ilosc_linii * sizeof(char*));
  czytanie_z_pliku(TablicaWString, ilosc_linii);
  int i = 0;

  /*for(i=0; i < ilosc_linii; i++){
    printf("%d. %s\n", i, TablicaWString[i]);
  }*/

  int rozmiar = 2000;
  Inf tab[rozmiar];
  reset_tab(tab, rozmiar);
  for(i = 0; i < 0.8*rozmiar; i++){
    HashInsert(tab, rozmiar, TablicaWString[i]);
  }

  printf("%d\n", ile_niepustych(tab, rozmiar));
  //Teraz posiadamy juz zzapelniona w 80% tablice teraz skasowac polowe elementow
  //potem zapelniamy ja z powrotem o ta polowe
  kasujpol(tab, rozmiar);
  //PrintTab(tab, rozmiar);

  for(i = rozmiar; i < rozmiar+(0.5*0.8*rozmiar); i++){
    HashInsert(tab, rozmiar, TablicaWString[i]);
  }

  printf("%d\n", ile_niepustych(tab, rozmiar));
  //PrintTab(tab, rozmiar);
  printf("Ilosc del : %d, rozmiar tablicy to %d\n ", CountDEL(tab, rozmiar), rozmiar);

  return 0;
}
int CountDEL(Inf tab[], int rozmiar){
  int i = 0;
  int licznik = 0;
  for(i=0; i < rozmiar; i++){
    if (tab[i].liczba == -1)
      licznik++;
  }
  return licznik;
}
void kasujpol(Inf tab[], int rozmiar){
  int i = 0;
  int licznik = 0;
  for(i = 0; i < rozmiar; i++){
    if(licznik%2 == 1){
      if(tab[i].nazwisko != NULL){
        tab[i].liczba = -1;
        tab[i].nazwisko = NULL;
      }
    }
    licznik++;
  }
}

int ile_niepustych(Inf tab[], int rozmiar){
  int licznik = 0;
  int i;
  for(i = 0; i < rozmiar; i++){
    if(tab[i].nazwisko != NULL)
      licznik++;
  }
  return licznik;
}

void czytanie_z_pliku(char **tab, int ilosc_linii){
  FILE *file = fopen("nazwiska.txt", "r");
  if(file == NULL){
    printf("Blad w otwarciu pliku nazwiska.txt\n");
    exit(0);
  }
  int i = 0;
  for(i = 0; i < ilosc_linii; i++){
    int tmp;
    char nazwisko[30];
    fscanf(file, "%d", &tmp);
    fscanf(file, "%s", nazwisko);
    tab[i] = (char*) malloc(30* sizeof(char));
    strcpy(tab[i], nazwisko);
  }
  fclose(file);
}

int licz_linie(){
  int ilosc = 0;
  FILE *file = fopen("nazwiska.txt", "r");
  if(file == NULL){
    printf("Blad w otwarciu pliku nazwiska.txt\n");
    exit(0);
  }
  char znak;
  do{
    znak = fgetc(file);
    if(znak == '\n')
      ilosc++;
  }while(znak != EOF);
  fclose(file);
  return ilosc;
}

void PrintTab(Inf tab[], int rozmiar){
  int i = 0;
  for(i = 0; i < rozmiar; i++){
    printf("%d. %d. %s\n", i, tab[i].liczba, tab[i].nazwisko);
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
  for(i = 0; i < strlen(nazwisko); i++){
    if((int)nazwisko[i] != 32)
      suma = suma + (int)nazwisko[i];
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
