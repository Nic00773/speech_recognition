#ifndef PRETREATMENT_H_
#define PRETREATMENT_H_

typedef struct segments_t {
  int trame, samplerate;
  float ** data;
} Segments;

// Take sound data with any amounts of channels and return a mono
// data by doing the average between the two channels
float *  make_mono    (float * data, SF_INFO file_info);

// Simple silence detection with threshold
float *  silence      (float * data, SF_INFO file_info, float threshold);

float *  preemphase   (float * data, SF_INFO file_info);

Segments segmentation (float * data, SF_INFO file_info);

complex float ** fft(Segments segments,int fft_length);

#endif
