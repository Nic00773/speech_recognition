#ifndef SIGNAL_ANALYSIS_H_
#define SIGNAL_ANALYSIS_H_

float module(float complex nb); //takes the module of a complex number
float **cepstral(complex float **segments, int trame, int fft_length); //put the module of every value of segments into a new float**

float hertz_to_mel (int i, int samplerate);
float mel_to_hertz(int samplerate, int i);

float fft_bin(int i, int samplerate, int fft_length);

float mel_filterbank(int m, int k);

double ** coef_cep(complex float **segment, int fft_length, int trame, int samplerate);

#endif
