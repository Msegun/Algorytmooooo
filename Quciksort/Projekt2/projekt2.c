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

  struct timespec time0, time1;
  printf("DANE LOSOWE (Czas sredni) : \n");
  printf("| Rozmiar N |    alg    |  alg zmod  |\n");
  int n = 0, i = 0;
  for(n = 100; n < 1501; n = n + 100){
    double Time=0, Czas_caly=0;
    double Time2=0, Czas_caly2=0;
    for(i = 0; i < n; i++){
      int tablica[n];
      int tablica2[n];
      randomowe_uzupelnienie(tablica, n);
      skopiowanie_wartosci(tablica, n, tablica2);
      clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&time0);
      quicksort(tablica, n, 0, n-1);
      clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&time1);
      Time = (time1.tv_sec+time1.tv_nsec/1000000000.0)-(time0.tv_sec+time0.tv_nsec/1000000000.0);
      Czas_caly = Czas_caly + Time;
      clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&time0);
      quicksortzmodyfikowany(tablica2, n, 0, n-1, 0.4*n);
      clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&time1);
      Time2 = (time1.tv_sec+time1.tv_nsec/1000000000.0)-(time0.tv_sec+time0.tv_nsec/1000000000.0);
      Czas_caly2 = Czas_caly2 + Time2;
    }
    Czas_caly = Czas_caly / n;
    Czas_caly2 = Czas_caly2 / n;
    printf("|%11d|%3.9lf|%3.10lf|\n", n, Czas_caly, Czas_caly2);
  }
  printf("PRZYPADEK NEGATYWNY : \n");
  printf("| Rozmiar N |    alg    |  alg zmod  |\n");
  for(n = 100; n < 1501; n = n + 100){
    double Time=0;
    double Time2=0;
    int tablica[n];
    int tablica2[n];
    negatywnyprzypadek(tablica, n);
    skopiowanie_wartosci(tablica, n, tablica2);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&time0);
    quicksort(tablica, n, 0, n-1);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&time1);
    Time = (time1.tv_sec+time1.tv_nsec/1000000000.0)-(time0.tv_sec+time0.tv_nsec/1000000000.0);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&time0);
    quicksortzmodyfikowany(tablica2, n, 0, n-1, 0.4*n);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&time1);
    Time2 = (time1.tv_sec+time1.tv_nsec/1000000000.0)-(time0.tv_sec+time0.tv_nsec/1000000000.0);
    printf("|%11d|%3.9lf|%3.10lf|\n", n, Time, Time2);
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
    if(p < r)
      insertionsort(tablica, rozmiar);
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
