#include "dtw.h"
#include "../NArr/src/narr.h"
#include "math.h"
#include <stdio.h>

#define MIN(a,b) (((a)<(b))?(a):(b))

double euclidean_distance(double * a, double * b) {
  int a_len = NArr_len(a);
  int b_len = NArr_len(b);
  int len   = MIN(a_len,b_len);

  double sum = 0;

  for (int i=0; i < len; i++) {
    double diff = a[i]-b[i];
    sum += diff*diff;
  }

  return sqrt(sum);
}

double dtw_distance (double ** actual, double ** training) {
  int m = NArr_len(actual);
  int n = NArr_len(training);

  double cost[m][n];

  cost[0][0] = euclidean_distance(actual[0], training[0]);
  for (int i=1; i < m; i++) cost[i][0] = cost[i-1][0] + euclidean_distance(actual[i], training[0]);
  for (int j=1; j < n; j++) cost[0][j] = cost[0][j-1] + euclidean_distance(actual[0], training[j]);

  for (int i=1; i<m; i++)
    for (int j=1; j<n; j++)
      cost[i][j] = MIN(cost[i][j-1],MIN(cost[i][j-1],cost[i-1][j-1]))
        + euclidean_distance(actual[i], training[j]);

  return cost[m-1][n-1];
}
