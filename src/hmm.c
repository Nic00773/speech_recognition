#include "hmm.h"
#include <stdlib.h>
#include <stdio.h>
#include "../NArr/src/narr.h"
#include <time.h>
#include <math.h>

Model * new_HMM (double ** x, int T, int L, int N) {
  Model * model = malloc(sizeof(Model));

  model->N = N;   // Initialize number of states
  model->L = L;   // Initialize dimensionality of data

  model->p0 = new_NArr(sizeof(double),N);

  model->a  = new_NArr(sizeof(double*),N);
  model->mu = new_NArr(sizeof(double*),N);
  for (int i = 0; i < N; i++) {
    model->a[i]  = new_NArr(sizeof(double),N);
    model->mu[i] = new_NArr(sizeof(double),L);
  }

  model->cov = new_NArr(sizeof(double*),L);
  for (int i=0; i < L; i++) {
    model->cov[i] = new_NArr(sizeof(double),L);
  }

  srand(time(0));
  double * global_mean = new_NArr(sizeof(double),L);

  // Find the global mean
  for (int d = 0; d < L; d++) {
    global_mean[d] = 0;
    for (int t = 0; t < T; t++) {
      global_mean[d] += x[t][d];
    }
    global_mean[d] /= T;
  }

  // Calculate the global diagonal covariance
  for (int d = 0; d < L; d++) {
    for (int e = 0; e < L; e++) model->cov[d][e] = 0;
    for (int t = 0; t < T; t++)
      model->cov[d][d] += (x[t][d] - global_mean[d]) * (x[t][d] - global_mean[d]);
    model->cov[d][d] /= T-1;
  }

  // Set all means close to the global means
  for (int i=0; i < N; i++) {
    for (int d = 0; d < L; d++)
      model->mu[i][d] = global_mean[d] + (.5 * rand() / (double) RAND_MAX - .25) * sqrt(model->cov[d][d]);
  }

  // Random initial and transition probs
  int s = 0;
  for (int i=0; i < N; i++) {
    model->p0[i] = 1 + rand() / (double) RAND_MAX;
    s += model->p0[i];
    int ss = 0;
    for (int j=0; j < N; j++) {
      model->a[i][j] = 1 + rand() / (double) RAND_MAX;
      ss += model->a[i][j];
    }
    for (int j = 0; j < N; j++) {
      model->a[i][j] /= ss;
    }
  }
  for (int i = 0; i < N; i++) model->p0[i] /= s;

  delete_NArr(global_mean);

  return model;
}

void delete_HMM (Model * model) {

  for (int i=0; i < model->N; i++) {
    delete_NArr(model->a[i]);
    delete_NArr(model->mu[i]);
  }

  for (int i=0; i < model->L; i++) {
    delete_NArr(model->cov[i]);
  }

  delete_NArr(model->a);
  delete_NArr(model->mu);
  delete_NArr(model->cov);

  free(model);
}

void HMM_print (Model * model) {
  printf("p0:\n");
  for (int i = 0; i < model->N; i++)
    printf("%f", model->p0[i]);
  printf("\n\na:\n");
  for (int i = 0; i < model->N; i++) {
    for (int j = 0; j < model->N; j++)
      printf("%f ", model->a[i][j]);
    printf("\n");
  }
  printf("\n\nmu:\n");
  for (int i = 0; i < model->N; i++) {
    for (int j = 0; j < model->L; j++)
      printf("%f ", model->mu[i][j]);
    printf("\n");
  }
  printf("\n\ncov:\n");
  for (int i = 0; i < model->L; i++)
  {
    for (int j = 0; j < model->L; j++)
      printf("%f ", model->cov[i][j]);
    printf("\n");
  }
  printf("\n\n");
}
