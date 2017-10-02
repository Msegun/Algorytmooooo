/********************************
*        TOMASZ ADAMCZYK        *
*       Nr albumu: 243217       *
*      Informatyka II ROK       *
*     Projekt3.c - ALL.6.6      *
********************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MDN 255
#define MIN_A 32
#define MAX_A 127

char **A, **B, **TMP;
unsigned int *Length;

/*void ReadFromCons(char **A, int n){
  char word[MDN];
  int i=0;
  for (i=0; i<n; i++){
    scanf("%s", word);
    A[i] = (char*) malloc(MDN * sizeof(char*));
    strcpy(A[i], word);
  }
}

void PrintArr(char **A, int n){
  int i;
  for (i=0; i<n; i++)
    printf("%s\n", A[i]);
}*/

void GetLength(char **A, int n){
  int i;
  for (i=0; i<n; i++)
    Length[i] = strlen(A[i]);
}

int MaxLength(char **A, int n){
  unsigned int max = 0;
  int i;
  for (i=0; i<n; i++)
    if (max<=Length[i]) max = Length[i];
  return max;
}

void ToEqualLength(char **A, int n, int max){
  int i, j;
  for (i=0; i<n; i++)
    for (j=strlen(A[i]); j<max; j++)
      A[i][j]=' ';
}

void CountingSort(char **A, char **B, int n, int p){
  int i, j;
  int C[MAX_A];
  for (i=0; i<MAX_A; i++)
    C[i]=0;
  for (j=0; j<n; j++)
    C[(int)A[j][p]]++;
  for (i=MIN_A; i<MAX_A; i++)
    C[i]+=C[i-1];
  for (j=n-1; j>=0; j--){
    B[C[(int)A[j][p]]-1]=A[j];
    C[(int)A[j][p]]--;
  }
}

void RadixSort(char **A, char **B, int n, int max){
  int i;
  for (i=max-1; i>=0; i--){
    CountingSort(A, B, n, i);
    TMP = A;
    A = B;
    B = TMP;
  }
}

int main(int argc, char* argv[]){
  FILE *in, *out;
  in = fopen(argv[1], "r");
  if (!in){
    fprintf(stderr, "Nie ma takiego pliku %s\n", argv[1]);
    exit(-1);
  }
  int n, i;
  fscanf(in, "%d", &n);
  A = (char**) malloc(n * sizeof(char*));
  B = (char**) malloc(n * sizeof(char*));
  TMP = (char**) malloc(n * sizeof(char*));
  for (i=0; i<n; i++){
    char word[MDN];
    fscanf(in, "%s", word);
    A[i] = (char*) malloc(MDN * sizeof(char*));
    strcpy(A[i], word);
  }
  fclose(in);
  Length = (unsigned int*) malloc(n * sizeof(unsigned int*));
  GetLength(A, n);
  int max = MaxLength(A, n);
  ToEqualLength(A, n, max);
  RadixSort(A, B, n, max);
  out = fopen(strcat(argv[1], ".out"), "w");
  for (i=0; i<n; i++) fprintf(out, "%s\n", A[i]);
  printf("Sortowanie zrobione. Zapisano w %s\n", argv[1]);
  fclose(out);
  return 0;
}
