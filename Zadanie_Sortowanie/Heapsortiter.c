#include <stdio.h>
#include<stdlib.h>

int ilosc_linii(char *nazwa);
void wypelnienie(char *nazwa, int tab[], int rozmiar);
void Heapify(int tab[], int rozmiarkopca, int i);
void BuildHeap(int tab[], int rozmiar);
void Heapsort(int tab[], int rozmiar);
void zapisanie(char *nazwa, int tab[], int rozmiar);

int main(int arg_num, char* arg[]){

if(arg_num == 3)
{
	int linie, i;
	linie = ilosc_linii(arg[1]);
	int tablica[linie];
	wypelnienie(arg[1], tablica, linie);
	printf("Tablica przed posortowaniem:\n");
	for(i=0; i<linie; i++)
		printf("%d ", tablica[i]);
	Heapsort(tablica, linie);
	printf("\nTablica po posortowaniu:\n");
	for(i=0; i<linie; i++)
		printf("%d ", tablica[i]);
	zapisanie(arg[2], tablica, linie);
}
else
		printf("Zle wywolanie ./a.out liczby.txt wynik.txt");

	return 0;
}

int ilosc_linii(char *nazwa){
	int i = 0;
	FILE *plik = fopen(nazwa, "r");
	if(plik == NULL){
		printf("Blad w otwarciu pliku\n");
		exit(0);
	}
	int get;
	do {
		get = fgetc(plik);
		if(get == '\n')
			i++;
	} while(get != EOF);

	fclose(plik);

	return i;
}

void wypelnienie(char *nazwa, int tab[], int rozmiar){
	int i;
	FILE *plik = fopen(nazwa, "r");
	if(plik == NULL){
		printf("Blad w otwarciu pliku\n");
		exit(0);
	}
	for(i=0; i < rozmiar; i++)
		fscanf(plik, "%d\n", &tab[i]);
	fclose(plik);
}

void Heapify(int tab[], int rozmiarkopca, int i){

   while (i <= rozmiarkopca){
     int najwiekszy, tmp;
     int l = i*2 + 1;
     int r = i*2 + 2;
     if (l<rozmiarkopca && tab[l] > tab[i])
       najwiekszy = l;
     else
       najwiekszy = i;
     if (r<rozmiarkopca && tab[r] > tab[najwiekszy])
       najwiekszy = r;
     if (najwiekszy != i){
       tmp = tab[najwiekszy];
       tab[najwiekszy] = tab[i];
       tab[i] = tmp;
       i = najwiekszy;
     }
     else
        return;//break;
    }
}

void BuildHeap(int tab[], int rozmiar){
	int i;
	for(i = rozmiar/2-1; i >= 0; i--)
		Heapify(tab, rozmiar, i);
}

void Heapsort(int tab[], int rozmiar){
	int tmp;
	BuildHeap(tab, rozmiar);
	int i;
	for(i = rozmiar - 1; i >= 0; i--){
		tmp = tab[i];
		tab[i] = tab[0];
		tab[0]= tmp;
		Heapify(tab, i, 0);
	}
}

void zapisanie(char *nazwa, int tab[], int rozmiar)
{
    int i;
    FILE *plik = fopen(nazwa, "w");

	for(i=0; i < rozmiar; i++)
	{
		fprintf(plik, "%d\n", tab[i]);
	}
	fclose(plik);
}
