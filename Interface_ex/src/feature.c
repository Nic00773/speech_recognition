#include <sndfile.h>
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <string.h>
#include "mfcc.h"
#include "../NArr/src/narr.h"

double ** do_mfcc (char * file_str) {
  SF_INFO file_info;
  SNDFILE * file = sf_open(file_str, SFM_READ, &file_info);

  int nb_samples   = file_info.channels * file_info.frames;
  int samplerate   = file_info.samplerate;
  double * samples = new_NArr(sizeof(double),nb_samples);

  sf_read_double(file, samples, nb_samples);
  return mfcc(samples,file_info.samplerate);
}

void write_mfcc(double ** data, char * output) {

  int h = NArr_len(data);
  int w = NArr_len(data[0]);

  FILE * file_output = fopen(output,"w");
  fprintf(file_output, "%d\n%d\n", h, w);

  for (int i=0; i < h; i++) {
    for (int j=0; j < w-1; j++) {
      fprintf(file_output, "%lf ", data[i][j]);
    }
    fprintf(file_output,"%lf\n",data[i][w-1]);
  }
  fclose(file_output);
}

int main (int argc, char * argv[]) {
  char * wavfile = argv[1];
  char * output  = argv[2];

  double ** mfcc = do_mfcc(wavfile);
  write_mfcc(mfcc,output);
  return 0;
}
