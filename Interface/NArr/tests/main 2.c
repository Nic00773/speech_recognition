#include "../src/narr.h"
#include <stdlib.h>
#include <stdio.h>


int main() {
  int * data = new_NArr(sizeof(int), 5);
  printf("%d\n", NArr_len(data));
  delete_NArr(data);
}
