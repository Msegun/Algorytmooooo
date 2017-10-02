#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int partition(int tablica[], int rozmiar, int p, int r);
void quicksort(int tablica[], int rozmiar, int p, int r);

int main(){

  srand(time(NULL));
  int n;
  scanf("%d", &n);
  int tablica[n];
  int i;
  struct timespec tp0, tp1;
  for(i=0; i<n; i++){
    tablica[i]=rand()%200;
    printf("%d ", tablica[i]);
  }
  double Tn=0;
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
  quicksort(tablica, n, 0, n-1);
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
  Tn=(tp1.tv_sec+tp1.tv_nsec/1000000000.0)-(tp0.tv_sec+tp0.tv_nsec/1000000000.0);
  printf("\n");
  for(i=0; i<n; i++){
    printf("%d ", tablica[i]);
  }
  printf("|%17lf|", Tn);
  return 0;
}

int partition(int tablica[], int rozmiar, int p, int r){
  int j;
  int temp, x = tablica[r];
  int i = p - 1;

  for(j=p; j < r; j++){
    if(tablica[j] <= x){
      i++;
      temp = tablica[i];
      tablica[i] = tablica[j];
      tablica[j] = temp;
    }
  }
  temp = tablica[r];
  tablica[r] = tablica[i+1];
  tablica[i+1] = temp;

  return i+1;
}

void quicksort(int tablica[], int rozmiar, int p, int r){
  int q;

  if(p < r){
    q = partition(tablica, rozmiar, p, r);
    quicksort(tablica, rozmiar, p, q-1);
    quicksort(tablica, rozmiar, q+1, r);
  }

}
