#include <sndfile.h>
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <string.h>
#include <unistd.h>
#include "gnuplot.h"
#include "mfcc.h"
#include "../NArr/src/narr.h"
#include "dtw.h"

#define DATAS_LEN 7
#define VOC_LEN   3

double ** do_mfcc (char * file_str) {
  SF_INFO file_info;
  SNDFILE * file = sf_open(file_str, SFM_READ, &file_info);

  int nb_samples   = file_info.channels * file_info.frames;
  int samplerate   = file_info.samplerate;
  double * samples = new_NArr(sizeof(double),nb_samples);

  sf_read_double(file, samples, nb_samples);
  return mfcc(samples,file_info.samplerate);
}

int main (int argc, char * argv[]) {

  if (argc < 2) {
    printf("Usage:\n%s file.wav\n", argv[0]);
    return 1;
  }
  
  // LEARNING
  char * datas[]      = {"1","2","3","4","5","6","7"};
  char * vocabulary[] = {"OUI","NON","OUVRIR"};

  double **** mfccs   = new_NArr(sizeof(double***),VOC_LEN);
  for (int i=0; i < VOC_LEN; i++) {
    mfccs[i] = new_NArr(sizeof(double**),DATAS_LEN);
  }
  
  for (int i = 0; i < VOC_LEN; i++) {
    printf("Learning word \"%s\" ....\n\n",vocabulary[i]);
    for (int j = 0; j < DATAS_LEN; j++) {
      char path[100];
      strcpy(path, "data/training/");
      strcat(path, vocabulary[i]);
      strcat(path, "/");
      strcat(path, datas[j]);
      strcat(path, ".wav");
      printf("Computing for %s...\n", path);
      int x = random() %100;
      usleep(x);
      mfccs[i][j] = do_mfcc(path);
    }
  }
  printf("\n\n");
  printf("Computing for %s...\n", argv[1]);
  double ** mfcc_file = do_mfcc(argv[1]);

  printf("\n\n-------------------------------------------------\n\n");

  printf("Comparing input with dictionary ....\n\n");
  double * result = new_NArr(sizeof(double), VOC_LEN);

  for (int i=0; i < VOC_LEN; i++) {
    result[i] = 0.;
    for (int j=0; j < DATAS_LEN; j++) {
      result[i] += dtw_distance(mfcc_file,mfccs[i][j]);
    }
    result[i] /= DATAS_LEN;
    printf("Score with %s: %lf\n", vocabulary[i], result[i]);
  }

  int min = 0;
  for (int i = 1; i < VOC_LEN; i++) {
    if (result[i] < result[min]) min = i;
  }

  printf("\n\n ====> %s <==== \n\n", vocabulary[min]);

  return 0;
}
