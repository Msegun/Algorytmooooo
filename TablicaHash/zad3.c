#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct struktura
{
    int liczba;
    char *nazwisko;
} strukturka;

void Wypelnienie(strukturka Zawartosc[] ,int rozmiar);
void reset_tab(strukturka tab[], int rozmiar);
void WstawienieWartosci(strukturka Zawartosc[], strukturka ZawartoscKodowana[], int rozmiar);
int StringNaINT(char *word);
int Hash(int k, int i, int rozmiar);
void Drukujtablicehaszowa(strukturka ZawartoscKodowna[], int rozmiar);

int main(){
  strukturka Zawartosc[2000];//80% to 1600 bd 800 kasował i potem dodawal 800 innych
  Wypelnienie(Zawartosc, 2000);//Nasza strukutura ktora bd zawierac 2k roznych struktur liczba nazwisko
  strukturka ZawartoscKodowana[2000];
  reset_tab(ZawartoscKodowana, 2000);
  int i = 0;
  WstawienieWartosci(Zawartosc, ZawartoscKodowana, 2000);
/*
  for(i=0; i < 4; i++){
    printf("%d, %d, %s\n", i, Zawartosc[i].liczba, Zawartosc[i].nazwisko);
  }
*/
  Drukujtablicehaszowa(ZawartoscKodowana, 2000);

  return 0;

}

void Wypelnienie(strukturka Zawartosc[] ,int rozmiar){
  FILE *file;
  file = fopen("nazwiska.txt", "r");

  if(file == NULL)
  {
      printf("\nBłąd w otwarciu pluku\n");
      exit(0);
  }
  int i;
  for(i=0; i<2000; i++)
  {
    int temp;
    char slowo[100];
    fscanf(file, "%d", &temp);
    fscanf(file, "%s", slowo);
    Zawartosc[i].liczba = temp;
    Zawartosc[i].nazwisko = (char*)malloc(100*sizeof(char));
    strcpy(Zawartosc[i].nazwisko, slowo);
  }

  fclose(file);
}

void reset_tab(strukturka tab[], int rozmiar){
  int i;
  for(i = 0; i < rozmiar; i++){
    tab[i].liczba = 0;
    tab[i].nazwisko = NULL;
  }
}

int Hash(int k, int i, int rozmiar){
  //[OL]
  int suma;
  k = k%rozmiar;
  suma = (k+i)&rozmiar;
  return suma;
}


void WstawienieWartosci(strukturka Zawartosc[], strukturka ZawartoscKodowana[], int rozmiar){
  int i = 0, wynik=0;
  int indexTabl = 0;
  for(i = 0; i < 1600; i++){
    indexTabl = StringNaINT(Zawartosc[i].nazwisko);
    int j = 0;
    do{
      wynik=Hash(indexTabl, j, rozmiar);
      if(ZawartoscKodowana[wynik].liczba == 0 || ZawartoscKodowana[wynik].liczba == -1){
        ZawartoscKodowana[wynik].nazwisko = Zawartosc[i].nazwisko;
        ZawartoscKodowana[wynik].liczba = Zawartosc[i].liczba;
        break;
      }
      j++;
    }
    while(j < rozmiar);
  }
}

int StringNaINT(char *word){//HaszowaniePolega po prostu zsumowaniu i mnozenu wyniku * stała X
  int i;
  int suma = 0;
  int x = 1;
  for(i = 0; i<strlen(word); i++){
    if((int)word[i] != 32)
      suma = suma *x +(int)word[i];
      suma = suma%2000;
  }
  return suma;
}

void Drukujtablicehaszowa(strukturka ZawartoscKodowna[], int rozmiar){
  int i = 0;
  for(i=0;i<rozmiar;i++){
    if((ZawartoscKodowna[i].liczba != 0 || ZawartoscKodowna[i].liczba != -1)&& ZawartoscKodowna[i].nazwisko != NULL)
      printf("%d, %d, %s\n", i, ZawartoscKodowna[i].liczba, ZawartoscKodowna[i].nazwisko);
  }
}
