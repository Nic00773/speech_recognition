#include <sndfile.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#ifndef M_PI
    #define M_PI 3.14159265358979323846f
#endif

// save a graph with an array of float
void print_graph (float * data, int data_size, char * graph_name, char * png_name) {
  FILE * gp = popen("gnuplot","w");
  fprintf(gp, "set term png\n");
  fprintf(gp, "set out \"%s\"\n", png_name);
  fprintf(gp, "set yrange [-1:1]\n");
  fprintf(gp, "set xrange [0:%d]\n", data_size);
  fprintf(gp, "plot '-' with lines title \"%s\"\n", graph_name);

  for (int i=0; i < data_size; ++i)
    fprintf(gp, "%f\n", data[i]);
  fprintf(gp,"e\n");

  fflush(gp);
  pclose(gp);
}

// Take sound data with any amounts of channels and return a mono
// data by doing the average between the two channels
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

int main (int argc, char * argv[]) {
  SF_INFO file_info;
  if (argc < 2) {
    printf("Usage:\n%s file.wav\n", argv[0]);
    return 1;
  }
  SNDFILE * file = sf_open(argv[1], SFM_READ, &file_info);

  int nb_samples = file_info.channels * file_info.frames;
  float * samples  = malloc(nb_samples*sizeof(float));
  int samplerate = file_info.samplerate/50;
  int trame = (nb_samples/samplerate)+2;
  float ** segmentation;
  segmentation=malloc(trame * sizeof(float*));
  for(int i=0; i<trame; i++)
    {
    segmentation[i]=malloc(samplerate*sizeof(float));
    }
  sf_read_float(file, samples, nb_samples);

  float * mono = make_mono(samples, file_info);

  // Print the data
  print_graph (mono, file_info.frames, argv[1], "waveform.png");

  // Pre-accentuation
  float * preemphase = malloc(sizeof(float)*file_info.frames);
  preemphase[0] = mono[0];
  for (int i=1; i < file_info.frames; ++i) {
    preemphase[i] = mono[i] - 0.9 * mono[i-1];
  }

  // Print the preemphase
  print_graph (preemphase, file_info.frames, argv[1], "preemphase.png");

  int k=0;
  printf("%d\n",nb_samples);
  for(int i=0; i<nb_samples; i++){
    if(i % samplerate==0)
    {
      k++;
    }
    segmentation[k][i % samplerate]=samples[i];
  }

  //fenetrage
  float n= samplerate/(nb_samples-1);
  float w=0.54f - 0.46f* cosf(n*M_PI);
  for(int i=0; i< trame; i++)
    for(int j=0; j<samplerate;j++)
    {
      segmentation[i][j]*=w;
    }
  //fenetrage
  free(samples);
  free(mono);
  for(int i=0; i<trame;i++)
    free(segmentation[i]);
  free(segmentation);
  free(preemphase);
  sf_close(file);

  return 0;
}
