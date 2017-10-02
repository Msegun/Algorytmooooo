#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Info{
  int liczba;
  char *nazwisko;
}Inf;

int H(int k, int i, int rozmiar);
int liczba_linii();
void Wczytywanie(char **tablica, int ilosc_linii);
void WczytywanieDoTabH(char **tablica, Inf tabH[], int ilosc_linii);

int main(){
  char **Tab;
  int n;
  n = liczba_linii();
  Tab = (char**) malloc(n*sizeof(char*));
  Inf TabH[n];
  Wczytywanie(Tab, n);
  WczytywanieDoTabH(Tab, TabH, n);
  free(Tab);
  return 0;
}


int H(int k, int i, int rozmiar){
  //[OL]
  int suma;
  k = k%rozmiar;
  suma = (k+i)%rozmiar;
  return suma;
}

void Wczytywanie(char **tablica, int ilosc_linii){
  FILE *file;
  file = fopen("nazwiska.txt", "r");
  if (file == NULL)
  {
  printf("\nBład otwarcia pliku\n");
  exit(0);
  }
  int i;
  for(i=0; i<ilosc_linii; i++)
  {
      int tmp;
      char slowo[100];
      fscanf(file, "%d", &tmp);
      fscanf(file, "%s", slowo);
      tablica[i] = (char*)malloc(100 * sizeof(char));
      strcpy(tablica[i],slowo);
  }
  fclose(file);
}

int liczba_linii(){
	FILE *file = fopen("nazwiska.txt", "r");
	if (file == NULL)
	{
		printf("\nNie mozna otworzyc pliku !\n");
		exit(0);
	}
	int counter=0;
	int ch;

	do
	{
		ch = fgetc(file);
		if(ch == '\n')
			counter++;
	} while (ch != EOF);

	if(ch != '\n' && counter != 0)
		counter++;

	fclose(file);
	return counter;
}

void WczytywanieDoTabH(char **tablica, Inf tabH[], int ilosc_linii){
  int i, j;
  int suma;
  int x=1;
  for(i=0; i<ilosc_linii; i++){
    suma = 0;
    for(j=0; i<100; j++)
    {
      if((int)tablica[i][j] != 32)
        suma = suma * x + (int)tablica[i][j];
    }
    tabH[i].liczba = suma;
    tabH[i].nazwisko = tablica[i];
  }
}
