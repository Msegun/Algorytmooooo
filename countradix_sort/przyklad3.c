#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>      // na potrzeby tolower

#define DLUGOSC_NAPISU 30
#define ILOSC_NAPISOW 5
#define ZAKRES_WARTOSCI_A 128

char **A; // wejsciowa tablica do posortowania
char **B; // wynikowa tablica, juz posortowana
char **pom;

void sortPrzezZliczanie(char **A, char **B, int ilosc, int pozycja);
void sortPozycyjne(char **A, char **B, int NAJDLUZSZY);
void drukuj(char **tablica, int ilosc);
void czytaj(char **tablica, int ilosc);
int najdluzszyNapis(char **tablica, int ilosc);
void taSamaDlugosc(char **tablica, int ilosc, int NAJDLUZSZY);


int main(){

        A=(char**) malloc(ILOSC_NAPISOW*sizeof(char*));
        B=(char**) malloc(ILOSC_NAPISOW*sizeof(char*));
        pom=(char**) malloc(ILOSC_NAPISOW*sizeof(char*));
                int NAJDLUZSZY; // dlugosc najdluzszego napisu w tablicy A

        printf("Wpisz napisy do tablicy A:\n");
        czytaj(A,ILOSC_NAPISOW);
                NAJDLUZSZY=najdluzszyNapis(A,ILOSC_NAPISOW);
                taSamaDlugosc(A,ILOSC_NAPISOW,NAJDLUZSZY);

                sortPozycyjne(A,B,NAJDLUZSZY);

        printf("\nSlownikowo posortowana tablica:\n");
        drukuj(B,ILOSC_NAPISOW);

        return 0;
}

// Sortowanie pozycyjne - tablice indeksowane od 1

void sortPrzezZliczanie(char **A, char **B, int ilosc, int pozycja){
        int i,j;
        int C[128]; // pomocnicza tablica 'licznikow', ile razy wystepuje jaki znak w A


        for (i=0;i<=ZAKRES_WARTOSCI_A;i++) C[i]=0;
        for (j=1;j<=ilosc;j++)
                                C[A[j][pozycja]] +=1;
        for (i=1;i<=ZAKRES_WARTOSCI_A;i++)
                                C[i]=C[i]+C[i-1];
        for (j=ilosc;j>0;j--){
                B[C[A[j][pozycja]]]=A[j];
                C[A[j][pozycja]]=C[A[j][pozycja]]-1;
        }
}

void sortPozycyjne(char **A, char **B, int NAJDLUZSZY){         // wywoluje sortowanie przez zliczanie po kolei dla kazdej pozycji
                int i;
                for (i=NAJDLUZSZY; i>=0; i--){
                        sortPrzezZliczanie(A,B,ILOSC_NAPISOW,i);
                        pom=A;
                        A=B;
                        B=pom;                        // tablica wynikowa staje sie wejsciowa
                }
}

void drukuj(char **tablica, int ilosc){
        int i;
        for (i=1;i<=ilosc;i++)
                        //tablica[i]=toupper(tablica[i]);               // jako ze drukujemy naziwska, zmiana pierwszej litery na Wielka
                printf("%s \n", tablica[i]);
}

void czytaj(char **tablica, int ilosc){
        char slowo[DLUGOSC_NAPISU];
        int i,j;
        for (i=1;i<=ilosc; i++){
                scanf("%s",slowo);
                for (j=0;j<strlen(slowo);j++)
                                        slowo[j] = tolower(slowo[j]); // zmniejszam wielkosc litery
                tablica[i] = (char*) malloc(sizeof(char)*DLUGOSC_NAPISU);
                strcpy(tablica[i],slowo);
        }
}

int najdluzszyNapis(char **tablica, int ilosc){         // znajduje dlugosc najdluzszego napisu
                int i,max=0;
                for (i=1;i<=ilosc;i++)
                        if (strlen(tablica[i])>max) max=strlen(tablica[i]);
                return max;
}

void taSamaDlugosc(char **tablica, int ilosc, int NAJDLUZSZY){          // jesli dany string jest krotszy, niz najdluzszy
                                                                        // to uzupelnia brakujace miejsca nullami
                int i,j;
                for (i=1; i<=ilosc; i++)
                        for (j=0; j<=NAJDLUZSZY; j++)
                               if (!(96 < (int)tablica[i][j] && (int)tablica[i][j] < 123)) tablica[i][j]=0;
}
