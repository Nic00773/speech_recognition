#include <sndfile.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include "pretreatment.h"

#ifndef M_PI
  #define M_PI 3.14159265358979323846f
#endif

float * make_mono (float * data, SF_INFO file_info) {
  float * result = malloc(file_info.frames*sizeof(float));
  int nb_channels = file_info.channels;

  for (int i=0; i < file_info.frames-nb_channels; i++) {
    float frame = 0;
    for (int j=0; j < nb_channels; j++) {
      frame += data[i*nb_channels+j];
    }
    result[i] = frame / (float)nb_channels;
  }

  return result;
}

float * silence (float * data, SF_INFO file_info, float threshold) {
  float * result = malloc(file_info.frames*sizeof(float));

  for (int i = 0; i < file_info.frames; ++i) {
    if (data[i] > threshold || data[i] < threshold) result[i] = data[i];
    else result[i] = 0;
  }

  return result;
}

float * preemphase (float * data, SF_INFO file_info) {
  float * result = malloc(file_info.frames*sizeof(float));

  result[0] = data[0];
  for (int i=1; i < file_info.frames; ++i) {
    result[i] = data[i] - 0.9 * data[i-1];
  }

  return result;
}

Segments segmentation (float * data, SF_INFO file_info) {

  int nb_per_trame  = file_info.samplerate/50;
  int nb_samples  = file_info.channels * file_info.frames;
  int trame;
  if(nb_samples % nb_per_trame == 0)
	trame=nb_samples/nb_per_trame;
  else
 	trame=(nb_samples/nb_per_trame)+1;
  trame+=trame-1;
  float ** result = malloc(trame * sizeof(float*));
  for (int i=0; i<trame; ++i) {
    result[i] = malloc(nb_per_trame*sizeof(float));
  }

  int k = 0,i=0, index=0, j=1, m= nb_per_trame/2;
  int l=m;
  result[k][i]=data[i];
  i++;
    while(k<trame && i<nb_samples){
	if(i % (nb_per_trame)==0)
		k+=2;
	result[k][i%(nb_per_trame)]=data[i];
	i++;
  }
  while(j<=trame-1){
    result[j][index]=data[m];
	m++;
	index++;
	if(m % (l+nb_per_trame)==0){
		j+=2;
		l=m;
		index=0;
	}
  }


  int   n = nb_per_trame/(file_info.frames-1);
  float w = 0.54f - 0.46f * cosf(n*M_PI);
  for (int i=0; i < trame; i++) {
    for (int j=0; j< nb_per_trame; j++) {
      result[i][j]*=w;
    }
  }

  Segments segments;
  segments.trame      = trame;
  segments.samplerate = nb_per_trame;
  segments.data       = result;

  return segments;
}

complex float complexp (float complex nb) {
  float x = crealf(nb);
  float y = cimagf(nb);
  return expf(x) * cosf(y) + I * expf(y) * sinf(y);
}

complex float **  fft (Segments segments, int fft_length) {
  complex float ** result = malloc(sizeof(complex float *) * segments.trame);
  for (int i = 0; i < segments.trame; ++i) {
    result[i] = malloc(sizeof(complex float) * fft_length);
    for (int k = 0; k < fft_length; k++) {
      complex float part = (-2 * M_PI * I * (k+1)) / segments.samplerate;
      for (int j = 0; j <  segments.samplerate; j++) {
        result[i][k] += segments.data[i][j] * complexp(part*(j+1));
      }
    }
  }
  return result;
}
