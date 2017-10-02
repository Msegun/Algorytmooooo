#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MDN 254

char **TAB1; //Deklarujemy tablice pierwsza do posortowania
char **TAB2; //Deklarujemy tablice wynikową
char **POMOCNICZA;

void Uzupelnijtablice(char **tab, int rozmiar);
void printtab(char **tab, int rozmiar);
int szukanienajdluzszego(char **tab, int rozmiar);
void roznedlugosci(char **tab, int rozmiar, int najdluzszynapis);
void radix_sort(char **tab1, char **tab2, int najdluzszynapis, int rozmiar);
void counting_sort(char **tab1, char **tab2, int rozmiar, int pozycja);

int main(){
  int n;
  printf("Podaj ile chcesz napisów: ");
  scanf("%d", &n);

  TAB1=(char**) malloc(n*sizeof(char*));
  TAB2=(char**) malloc(n*sizeof(char*));
  POMOCNICZA=(char**) malloc(n*sizeof(char*));

  int najdluzszynapis;
  Uzupelnijtablice(TAB1, n);
  //printf("\n");//do sprawdzenia ze dobrze wpisuje
  //printtab(TAB1, n);//to tez
  najdluzszynapis = szukanienajdluzszego(TAB1, n);
  roznedlugosci(TAB1, n, najdluzszynapis);
  printf("\n");
  //printtab(TAB1, n);
  //printf("%d", najdluzszynapis);//czy dobry rozmiar
  radix_sort(TAB1, TAB2, najdluzszynapis, n);
  printtab(TAB2, n);
  return 0;
}

void Uzupelnijtablice(char **tab, int rozmiar){
  char slowo[MDN];
  int i, j;
  for(i = 1; i <= rozmiar; i++){
    scanf("%s", slowo);
    for(j = 0; j < strlen(slowo); j++)
      slowo[j] = tolower(slowo[j]);
    tab[i] = (char*) malloc(sizeof(char)*MDN);
    strcpy(tab[i],slowo);
  }
}

void printtab(char **tab, int rozmiar){
  int i;
  for(i = 1; i<=rozmiar; i++)
    printf("%s \n", tab[i]);
}
int szukanienajdluzszego(char **tab, int rozmiar){
  int i;
  int dlugoscmaks = 0;
  for(i=1; i<=rozmiar; i++)
    if (strlen(tab[i])>dlugoscmaks)
     dlugoscmaks=strlen(tab[i]);
  return dlugoscmaks;
}

void roznedlugosci(char **tab, int rozmiar, int najdluzszynapis){
  int i,j;
  for (i=1; i<=rozmiar; i++)
          for (j=0; j<=najdluzszynapis; j++)
                  if (!(96 < (int)tab[i][j] && (int)tab[i][j] < 123)){//sprawdzam czy jest od a-z
                    if(!((int)tab[i][j] > 47 && (int)tab[i][j] < 58))//sprawdzam czy jest od 0-9
                      tab[i][j]=0;//jestli nie jest to wstawiam null char = 0 -> null
                  }
}

void radix_sort(char **tab1, char **tab2, int najdluzszynapis, int rozmiar){
  int i;
  for(i = najdluzszynapis - 1; i>=0; i--){
    counting_sort(tab1, tab2, rozmiar, i);
    POMOCNICZA = tab1;
    tab1 = tab2;
    tab2 = POMOCNICZA;
  }
}

void counting_sort(char **tab1, char **tab2, int rozmiar, int pozycja){
  int i,j;
  int C[128];
  for (i=0; i<=128; i++)
    C[i]=0;
  for (j=1;j<=rozmiar;j++){
    if(i==1)
      C[i]=C[i];
    C[tab1[j][pozycja]] +=1;
  }
  for (i=1;i<=128;i++)
    C[i]=C[i]+C[i-1];
  for (j=rozmiar;j>0;j--){
    tab2[C[tab1[j][pozycja]]]=tab1[j];
    C[tab1[j][pozycja]]=C[tab1[j][pozycja]]-1;
  }
}
