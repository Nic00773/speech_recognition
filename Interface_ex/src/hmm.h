#ifndef HMM_H_
#define HMM_H_

typedef struct model_t {
  int N;              // number of states
  double* p0;         // initial probs
  double** a;         // transition probs
  int L;              // dimensionality of data
  double** mu;        // state means
  double** cov;       // covariance, tied between all states
} Model;

Model * new_HMM     (double ** x, int T, int L, int N);
void    delete_HMM  (Model * model);

void HMM_print(Model * model);

#endif
