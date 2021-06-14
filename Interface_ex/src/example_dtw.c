#include "dtw.h"
#include "../NArr/src/narr.h"
#include <stdio.h>

void print_narr(double ** mat) {
   for (int i=0; i < NArr_len(mat); i++) {
    for (int j=0; j < NArr_len(mat[0]); j++) {
      printf("%lf\t", mat[i][j]);
    }
    printf("\n");
  }
}

int main () {
  int N = 4;
  int M = 2;
  double ** a = new_NArr(sizeof(double*), N);
  double ** b = new_NArr(sizeof(double*), M);

  int i;
  double k = 1.;
  for (i=0; i < M; i++) {
    a[i] = new_NArr(sizeof(double),3);
    b[i] = new_NArr(sizeof(double),3);
    for (int j=0; j < 3; j++) a[i][j] = k++;
    for (int j=0; j < 3; j++) b[i][j] = k++;
  }
  for (; i < N; i++) {
    a[i] = new_NArr(sizeof(double),3);
    for (int j=0; j < 3; j++) a[i][j] = k++;
  }


  printf("A:\n");
  print_narr(a);

  printf("\n\nB:\n");
  print_narr(b);

  printf("\n\n");

  dtw_distance(a,b);

  return 0;
}
