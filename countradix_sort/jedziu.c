#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>      // na potrzeby tolower
 
#define DLUGOSC_NAPISU 30
#define ILOSC_NAPISOW 20000
#define ZAKRES_WARTOSCI_A 128
 
char **A; // input array to sort
char **B; // output sorted array
char **pom;
 
// Sortowanie pozycyjne - tablice indeksowane od 1
 
void sortPrzezZliczanie(char **A, char **B, int ilosc, int pozycja){ //counting sort
        int i,j;
        int C[2048]; // pomocnicza tablica 'licznikow', ile razy wystepuje jaki znak w A
 
 
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
 
void sortPozycyjne(char **A, char **B, int NAJDLUZSZY){         // radix sort
                int i;
                for (i=NAJDLUZSZY-1; i>=0; i--){
                        sortPrzezZliczanie(A,B,ILOSC_NAPISOW,i);
                        pom=A;A=B;B=pom;                        // input array to output
                }
}
 
void drukuj(char **tablica, int ilosc){
    FILE *fp;
 
    if ((fp=fopen("output.txt", "w"))==NULL) {
      printf ("Nie mogę otworzyć pliku input.txt do zapisu!\n");
      return;
      }
 
 
        int i;
        for (i=1;i<=ilosc;i++)
                        //tablica[i]=toupper(tablica[i]);
                fprintf(fp, "%s \n", tablica[i]);
     fclose (fp);
}
 
void czytaj(char **tablica, int ilosc){
 
    FILE *fp;
    int tmp;
    if ((fp=fopen("input.txt", "r"))==NULL) {
      printf ("Nie mogę otworzyć pliku output.txt do zapisu!\n");
      return;
      }
 
 
        char slowo[DLUGOSC_NAPISU];
        int i,j;
        for (i=1;i<=ilosc; i++){
                fscanf (fp, "%d", &tmp);
                fscanf(fp, "%s", &slowo);
               // for (j=0;j<strlen(slowo);j++)
                 //                       slowo[j] = tolower(slowo[j]); // zmniejszam wielkosc litery
                tablica[i] = (char*) malloc(sizeof(char)*DLUGOSC_NAPISU);
                strcpy(tablica[i],slowo);
        }
    fclose (fp);
}
 
int najdluzszyNapis(char **tablica, int ilosc){         // finds maximum length of word
                int i,max=0;
                for (i=1;i<=ilosc;i++)
                        if (strlen(tablica[i])>max) max=strlen(tablica[i]);
                return max;
}
 
void taSamaDlugosc(char **tablica, int ilosc, int NAJDLUZSZY){          // if string is lower than maximum then fill with nulls
 
                int i,j;
                for (i=1; i<=ilosc; i++)
                        for (j=0; j<=NAJDLUZSZY; j++)
                                if (!(96 < (int)tablica[i][j] && (int)tablica[i][j] < 123)) tablica[i][j]=0;
}
 
int main(){
        A=(char**) malloc(ILOSC_NAPISOW*sizeof(char*));
        B=(char**) malloc(ILOSC_NAPISOW*sizeof(char*));
        pom=(char**) malloc(ILOSC_NAPISOW*sizeof(char*));
                int NAJDLUZSZY; // length of the longest word
        czytaj(A,ILOSC_NAPISOW);
                NAJDLUZSZY=najdluzszyNapis(A,ILOSC_NAPISOW);
                taSamaDlugosc(A,ILOSC_NAPISOW,NAJDLUZSZY);
                sortPozycyjne(A,B,NAJDLUZSZY);
 
        drukuj(B,ILOSC_NAPISOW);
        return 0;
}
