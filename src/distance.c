#include <sndfile.h>
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <string.h>
#include "dtw.h"
#include "../NArr/src/narr.h"

double ** read_mfcc(char * input) {
  int h = 0, w = 0;
  double ** result;
  FILE * file_input = fopen(input,"r");
  fscanf(file_input, "%d\n",&h);
  fscanf(file_input, "%d\n",&w);

  result = new_NArr(sizeof(double*),h);
  for (int i=0; i < h; i++) {
    result[i] = new_NArr(sizeof(double),w);
    for (int j=0; j< w-1; j++) {
      fscanf(file_input, "%lf ", &result[i][j]);
    }
    fscanf(file_input, "%lf\n", &result[i][w-1]);
  }
  fclose(file_input);
  return result;
}

int main(int argc, char * argv[]) {

  double ** a;
  double ** b;

  a = read_mfcc(argv[1]);
  b = read_mfcc(argv[2]);

  double res = dtw_distance(a,b);

  printf("%lf", res);

  return 0;
}
