#include "narr.h"
#include <stdlib.h>

void * new_NArr(int size_data, int size) {
  int * data = malloc( size_data * size + sizeof(int) );
  *data++ = size;
  return (void*)data;
}

int NArr_len(void * data) {
  return *(((int*)data)-1);
}

void delete_NArr(void * data) { free( ((int*)data)-1 ); }
