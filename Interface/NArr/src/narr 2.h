#ifndef NARR_H_
#define NARR_H_

typedef struct narr_t {
  int size;
  void * data;
} NArr;

void * new_NArr(int size_data, int size);
int    NArr_len(void * data);
void   delete_NArr(void * data);

#endif
