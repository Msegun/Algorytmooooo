#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MLDD 1000000000.0 //10**10
// kompilowac z opcjami -lrt -lm, tj. np. gcc ALL_01.c -lrt -lm

void array_print(int arr[], int size);
void random_array(int arr[], int size);
void bad_array(int arr[], int size);
int partition(int arr[], int size, int p, int r);
void quicksort(int arr[], int size, int p,int r);
// ------ zad A 4.5
void quicksortToBubble(int arr[], int size, int p, int r, int stala);
void bubblesort(int arr[], int size);
void array_copy(int arr[], int size, int arr2[], int size2);

int main()
{
    int stala;
    printf("Podaj stala do quicksortToBubble!(1-100): ");
    scanf("%d", &stala);
    while (stala > 100 || stala < 1)
    {
      printf("Zla wartosc stalej!(przedzial musi byc od 1-100)!\n");
      printf("Nowa wartosc stalej: ");
      scanf("%d", &stala);
    }
    int n = 100;
    int arr[n];
/*  printf("\nTest dzialania funckji :\n");
    printf("Bad array:\n");
    bad_array(arr, n);
    array_print(arr, n);
    quicksort(arr, n, 0, n-1);
    array_print(arr, n);
    printf("Random array:\n");
    random_array(arr, n);
    array_print(arr, n);
    quicksort(arr, n, 0, n-1);
    array_print(arr, n);
    printf("\n");
*/
    struct timespec tp0, tp1;
    printf("Algorytm quicksort = alg1\n");
    printf("Algorytm quicksort toBubble = alg2\n");
    printf("|  N  |   alg1 bad    |   alg2 bad    |   alg1 rand   |   alg2 rand   |\n");
    for(n=100; n<2501; n=n+100)
    {
            double Tn, TnTmp,TnTotal=0;
            double Tn1, TnTmp1, TnTotal1=0;
            int tab[n];
            int tabcp[n]; //kopia do qsortToBubble!
            bad_array(tab, n);
            array_copy(tab,n, tabcp, n);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
            quicksort(tab, n, 0, n-1);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
            Tn=(tp1.tv_sec+tp1.tv_nsec/MLDD)-(tp0.tv_sec+tp0.tv_nsec/MLDD);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
            quicksortToBubble(tabcp, n, 0, n-1, stala);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
            Tn1=(tp1.tv_sec+tp1.tv_nsec/MLDD)-(tp0.tv_sec+tp0.tv_nsec/MLDD);
            int i;
            for(i=0; i<n; i++)
            {
                int tab1[n];
                int tab1cp[n];
                random_array(tab1, n);
                array_copy(tab1, n, tab1cp, n);
                clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
                quicksort(tab1, n, 0, n-1);
                clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
                TnTmp = (tp1.tv_sec+tp1.tv_nsec/MLDD)-(tp0.tv_sec+tp0.tv_nsec/MLDD);
                TnTotal = TnTotal + TnTmp;
                clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
                quicksortToBubble(tab1cp, n, 0, n-1, stala);
                clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
                TnTmp1 = (tp1.tv_sec+tp1.tv_nsec/MLDD)-(tp0.tv_sec+tp0.tv_nsec/MLDD);
                TnTotal1 = TnTotal1 + TnTmp1;
            }
            TnTotal = TnTotal/n;
            TnTotal1 = TnTotal1/n;
            printf("|%4d |%3.13lf|%3.13lf|%3.13lf|%3.13lf|\n", n, Tn, Tn1, TnTotal, TnTotal1);
    }

    return 0;
}

void array_print(int arr[], int size)
{
    int i;
	for(i = 0; i<size; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void random_array(int arr[], int size)
{
    int i;
    srand(time(NULL));
    for(i = 0; i < size; i++)
    {
        arr[i] = rand()%100;
    }
}

void bad_array(int arr[], int size)
{
    int i;
    for(i = 0; i < size; i++)
    {
        arr[i] = size - i;
    }

}

void bubblesort(int arr[], int size)
{
    int i;
    int tmp;
    if (size==0 || size==1)
        return;
    for (i=0; i<size-1; i++)
    {
        if (arr[i+1]<arr[i])
        {
            tmp = arr[i];
            arr[i] = arr[i+1];
            arr[i+1] = tmp;
        }
    }
    bubblesort(arr, size-1);
}


int partition(int arr[], int size, int p, int r)
{
    int j, tmp;
    int x=arr[r];
    int i=p-1;
    for(j=p; j<=r; j++)
    {
        if (arr[j] <= x)
        {
            i++;
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    }
    if (i<r) return i;
    else
        return i-1;
}

void quicksort(int arr[], int size, int p, int r)
{
    int q;
    if (p<r)
    {
        q = partition(arr, size, p, r);
        quicksort(arr, size, p, q);
        quicksort(arr, size, q+1, r);
    }
}

void quicksortToBubble(int arr[], int size, int p, int r, int stala)
{
    int q;
    if (r-p+1 < stala)
        bubblesort(arr, size-stala);
    if (p<r)
    {
        q = partition(arr, size, p, r);
        quicksort(arr, size, p, q);
        quicksort(arr, size, q+1, r);
    }
}

void array_copy(int arr[], int size, int arr2[], int size2) //from -> to
{
    int i;
    for(i=0; i<size2; i++)
    {
        arr2[i] = arr[i];
    }

}
