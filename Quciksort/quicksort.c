#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MLDD 1000000000.0 //10**10
// kompilowac z opcjami -lrt -lm, tj. np. gcc ALL_01.c -lrt -lm
// http://blog.matthewrathbone.com/2009/11/10/operation-algorithm-quicksort-in-c-and-scheme.html

void array_print(int arr[], int size);
void random_array(int arr[], int size);
void bad_array(int arr[], int size);
int partition(int arr[], int size, int p, int r);
void quicksort(int arr[], int size, int p,int r);

int main()
{
    int n = 10;
    printf("\nTest dzialania qsorta i funkcji wypelniajacych tablice:\n");
    int arr[n];
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
    struct timespec tp0, tp1;
    printf("|Rozmiar tablicy N|(sredni) czas - dane losowe|czas - dane niekorzystne|\n");
    for(n=10; n<251; n=n+10)
    {
            double Tn, TnTmp, TnTotal=0;
            int tab[n];
            bad_array(tab, n);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
            quicksort(tab, n, 0, n-1);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
            Tn=(tp1.tv_sec+tp1.tv_nsec/MLDD)-(tp0.tv_sec+tp0.tv_nsec/MLDD);
            int i;
            for(i=0; i<n; i++)
            {
                int tab1[n];
                random_array(tab1, n);
                clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
                quicksort(tab1, n, 0, n-1);
                clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
                TnTmp = (tp1.tv_sec+tp1.tv_nsec/MLDD)-(tp0.tv_sec+tp0.tv_nsec/MLDD);
                TnTotal = TnTotal + TnTmp;
            }
            TnTotal = TnTotal/n;
            printf("|%17d|               %3.10lf|            %3.10lf|\n", n, TnTotal, Tn);
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


int partition(int arr[], int size, int p, int r)
{
    int j, tmp;
    int x=arr[r];
    int i=p-1;
    for(j=p; j<r; j++)
    {
        if (arr[j] <= x)
        {
            i++;
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    }
    tmp = arr[r];
    arr[r] = arr[i+1];
    arr[i+1] = tmp;
    return i+1;
}

void quicksort(int arr[], int size, int p, int r)
{
    int q;
    if (p < r)
    {
        q = partition(arr, size, p, r);
        quicksort(arr,size, p, q-1);
        quicksort(arr, size, q+1, r);
    }
}
