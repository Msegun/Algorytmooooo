#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 2000
#define WSIZE 20

int H(int k,int i)
{
//[OK] adresowanie otwarte kwadratowe
//h(k) = k mod SIZE
//H(k, i) = (h(k) + i*i) mod SIZE
    int wynik;
    k = k%SIZE;
    wynik = (k+i*i)%SIZE;
    return wynik;
}

int HashInsert(int T[],int x)
{
// wstawia element x do tablicy z haszowaniem T
// wartoœæ NIL w tablicy to miejsce wolne
// wartoœæ DEL w tablicy to miejsce po usuniêtym elemencie

    int i, j;
    i = 0;
    do
    {
        j=H(x,i);
        if (T[j] == 0 || T[j] == -1) // -1 -> nasz DEL
        {
            //jesli bedzie mozna wstawic , licznik ++
            T[j] = x;
            return j;
        }
        i=i+1;
    }
    while(i < SIZE);
    //printf("Nie udalo sie wstawic elementu [%d] do tablicy haszujacej!\n", x);
    //licznik nieudanych prob wstawienia ++
    return 0;
}

int HashSearch(int T[], int k)
{
// szuka klucza k w tablicy z haszowaniem T
    int i, j;
    i = 0;
    do
    {
        j=H(k,i);
        if(T[j] == k)
        {
            printf("Udalo sie znalezc element [%d] w tablicy haszujacej na poz. [%d]\n", k, j);
            return j;
        }
        i=i+1;
    }
    while(T[j] != 0 && i<SIZE);
    printf("Nie udalo sie znalezc elementu [%d] w tablicy haszujacej!\n", k);
    return 0;
}

int HashDelete(int T[], int j)
{
// usuwa element z pozycji j w tablicy T wpisuj¹c na tê pozycjê znacznik DEL
    if(j < SIZE)
    {
        T[j] = -1;
        //printf("Udalo sie usunac element na poz. [%d]\n", j);
        return 1;
    }
    //printf("Nie udalo sie usunac elementu na poz. [%d], poniewaz %d >SIZE\n", j, j);
    return 0;
}

int max_len(char **tab, int ilosc_linii)
{
    int i, max=0;
    for(i=0;i<ilosc_linii;i++)
    {
        if(strlen(tab[i])>max)
        {
            max=strlen(tab[i]);
        }
    }
    return max;
}

void same_len(char **tab, int ilosc_linii, int max)
{
    int i, j;
    for (i=0; i<ilosc_linii; i++)
        for (j=strlen(tab[i]); j<max; j++)
            tab[i][j]=' ';
}

int lines_number(char *name)
{
	FILE *file = fopen(name, "r");
	if (file == NULL)
	{
		printf("\nNie mozna otworzyc pliku %s!\n", name);
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

void read_from_file(char **tab, char *name, int ilosc_linii)
{
    FILE *file;
    file = fopen(name, "r");
	if (file == NULL)
	{
		printf("\nNie mozna otworzyc pliku %s!\n", name);
		exit(0);
	}
    int i;
    for(i=0; i<ilosc_linii; i++)
    {
        char slowo[WSIZE];
        fscanf(file, "%s", slowo);
        tab[i] = (char*)malloc(WSIZE * sizeof(char));
        strcpy(tab[i],slowo);
    }
    fclose(file);
}

void array_reset(int arr[], int size)
{
    int i;
    for(i = 0; i<size; i++)
    {
        arr[i] = 0;
    }
}

void array_print(int arr[], int size)
{
    int i;
	for(i = 0; i<size; i++)
	{
	    if(arr[i] != 0)
        {
            //if(arr[i] != -1) //pokazemy bez pol usunietych!
            printf("%-4d. [%4d]\n", i, arr[i]);
        }
	}
	printf("\n");
}

void stringarray_to_intarray(char **tab1, int tab2[], int ilosc_linii, int max)
{
//w zmiennej "suma" dajemy jakies wymyslone przez nas kodowanie znaku
    int i, j;
    int suma;
    for (i=0; i<ilosc_linii; i++)
    {
        suma = 0;
        for (j=0; j<max; j++)
        {
            if(tab1[i][j] != ' ')
                suma += (int)tab1[i][j];
        }
        tab2[i] = suma;
    }
}


int main()
{
    char *file_name = "3700.txt";
    int n;
    n = lines_number(file_name);
    char **S;
    S = (char**) malloc(n * sizeof(char*));
    int Sint[n]; //tablica z kodowaniem Stringow na liczby
    read_from_file(S,file_name, n);
    int max = max_len(S, n);
    same_len(S, n, max);
    int T[SIZE];

    //--------------------------------------
    stringarray_to_intarray(S, Sint, n, max);
    printf("\nIlosc linii : %d\n", n);
    printf("Max len : %d\n", max);
    printf("%s\n",S[0]);
    printf("%d\n\n", Sint[0]);
    //---------------------------------------

    array_reset(T,SIZE);
    HashInsert(T,4);
    HashInsert(T,4);
    HashInsert(T,4);
    HashInsert(T,1001);
    array_print(T, SIZE);
    HashSearch(T,4);
    HashSearch(T,53);
    return 0;
}
