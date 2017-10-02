#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

int partition(int tablica[], int rozmiar, int p, int r);
void quicksort(int tablica[], int rozmiar, int p, int r);
void randomowe_uzupelnienie(int tablica[], int rozmiar);
void negatywnyprzypadek(int tablica[], int rozmiar);
void wypisanie(int tablica[], int rozmiar);
void quicksortzmodyfikowany(int tablica[], int rozmiar, int p, int r, int stala);
void insertionsort(int tablica[], int rozmiar);
void skopiowanie_wartosci(int tablica[], int n, int tablica2[]);

int main(){
  int i, j;

  for(i=0; i < 1; i++ ){
    int tab[15];
    randomowe_uzupelnienie(tab, 15);
    wypisanie(tab, 15);
    printf("Insertionsort: \n");
    insertionsort(tab, 15);
    wypisanie(tab, 15);
    printf("Ponownie zapiszemy nowe liczby i wypiszemy: \n");
    randomowe_uzupelnienie(tab, 15);
    wypisanie(tab, 15);
    printf("Qsort: \n");
    quicksortzmodyfikowany(tab, 15, 0, 14, 0.4*15);
    wypisanie(tab, 15);
  }

  return 0;
}

int partition(int tablica[], int rozmiar, int p, int r){
  int j, temp;
  int x = tablica[r];
  int i = p - 1;

  for(j = p; j <= r; j++){

    if(tablica[j] <= x){
      i++;
      temp = tablica[i];
      tablica[i] = tablica[j];
      tablica[j] = temp;
    }
  }

  if(i < r)
    return i;
  else
    return i-1;

}

void quicksort(int tablica[], int rozmiar, int p, int r){
  int q;
  if(p < r){
    q = partition(tablica, rozmiar, p, r);
    quicksort(tablica, rozmiar, p, q);
    quicksort(tablica, rozmiar, q+1, r);
  }
}

void insertionsort(int tablica[], int rozmiar){
  int i, j, wartosc;
  for(i = 1; i < rozmiar; i++){
    wartosc = tablica[i];
    for(j = i - 1; j >= 0 && tablica[j] > wartosc; j--)
      tablica[j + 1] = tablica[j];
    tablica[j + 1] = wartosc;
  }
}

void quicksortzmodyfikowany(int tablica[], int rozmiar, int p, int r, int stala){
  int q;
  if((r - p + 1) > stala){
    if(p < r){
      q = partition(tablica, rozmiar, p, r);
      quicksortzmodyfikowany(tablica, rozmiar, p, q, stala);
      quicksortzmodyfikowany(tablica, rozmiar, q+1, r, stala);
    }
  }
  else
    if(p < r && (r - p + 1 < stala)){
      insertionsort(tablica, rozmiar);
    }
  }

void randomowe_uzupelnienie(int tablica[], int rozmiar){
  srand(time(NULL));
  int i = 0;
  for(i = 0; i < rozmiar; i++)
    tablica[i] = rand()%250;
}

void negatywnyprzypadek(int tablica[], int rozmiar){
  int i=0;
  for(i = 0; i < rozmiar; i++)
    tablica[i] = rozmiar - i;
}

void wypisanie(int tablica[], int rozmiar){
  int i = 0 ;
  for(i = 0; i < rozmiar; i++)
    printf(" %d ", tablica[i]);
  printf("\n");
}

void skopiowanie_wartosci(int tablica[], int rozmiar, int tablica2[]){
  int i = 0;
  for(i = 0; i < rozmiar; i++)
    tablica2[i] = tablica[i];
}
