
#include <math.h>
#include <complex.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../NArr/src/narr.h"

float module(float complex nb){
float x=crealf(nb);
float y=cimagf(nb);
return sqrt((x*x)+(y*y));
}


float** cepstral(complex float **segments, int trame, int fft_length){
float **result=malloc(sizeof(float*)*trame);
for(int i=0;i<trame;i++)
	result[i]=malloc(sizeof(float)*fft_length);
for(int i=0;i<trame;i++)
	for(int j=0; j<fft_length; j++)
	result[i][j]=module(segments[i][j])*module(segments[i][j]);
	//result[i][j]=module(segments[i][j])*module(segments[i][j]/analysis_window);	//periodogram estimate of the power spectrum
return result;
}

float hertz_to_mel (int i , int samplerate){
	float low_bound = 1125.0*logf(1.0+(20.0/700.0));
	float upper_bound = 1125.0*logf(1.0+(samplerate/2.0/700.0));
	float gap=(upper_bound-low_bound)/27.0;
	return (low_bound+(i*gap)); 
}


float mel_to_hertz(int i, int samplerate)
{
    return 700*(expf(hertz_to_mel(i,samplerate)/1125.0)-1.0);
}

float fft_bin(int i, int samplerate,int fft_length)
{
    return floorf(((fft_length+1)*mel_to_hertz(i,samplerate))/samplerate);
}


float mel_filterbank(int m, int k,int samplerate, int fft_length)
{
	float fft_bin_minus=fft_bin(m-1, samplerate, fft_length);
	float fft_bin_m=fft_bin(m,samplerate,fft_length);
	float fft_bin_plus=fft_bin(m+1, samplerate, fft_length);

	if(k<fft_bin_minus)
		return 0;
	if(k>=fft_bin_minus && k<=fft_bin_m)
		return ((float)(k-fft_bin_minus))/(fft_bin_m-fft_bin_minus);
	if(k<=fft_bin_plus && k>=fft_bin_m)
		return (float)(fft_bin_plus-k)/(fft_bin_plus-fft_bin_m);
	else
		return 0;
}

double ** coef_cep(complex float **segments,int fft_length, int trame, int samplerate)
{
		float **power_spectrum=cepstral(segments, trame, fft_length);
		float **coef=malloc(sizeof(float*)*trame);
		float **coef_1=malloc(sizeof(float*)*trame);
		double **coef_final = new_NArr(sizeof(double*),trame);
		for(int i=0; i<trame; i++){
			coef[i]=malloc(sizeof(float)*26);
			coef_1[i]=malloc(sizeof(float)*26);
			coef_final[i] = new_NArr(sizeof(double),13);
		}
		for(int i=0; i<trame; i++){
			for(int m=0; m<26; m++){
				for(int k=0;k<=fft_length/2;k++){
					//printf("%d %d %d %f\n",i,m+1,k, mel_filterbank(m+1,k, samplerate, fft_length));
					coef[i][m]+=(mel_filterbank(m+1,k,samplerate,fft_length)*power_spectrum[i][k]);
				}
			}
		}

		for(int i=0; i<trame;i++){
			coef_1[i][0]=logf(coef[i][0]);
			for(int k=1;k<26;k++) 
				for(int m=1; m<26; m++)
				coef_1[i][k]+=logf(coef[i][m])*cosf((M_PI*k/26.0)*(m-(1.0/2.0)));
		}
		for(int i=0; i<trame; i++)
			for(int j=0; j<13; j++)
			coef_final[i][j]=coef_1[i][j];


		for(int i=0;i<trame;i++){
			free(power_spectrum[i]);
			free(coef[i]);
			free(coef_1[i]);
		}
		free(power_spectrum);
		free(coef);
		free(coef_1);
		return coef_final;
}

	





