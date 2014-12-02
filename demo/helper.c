#include <stdio.h>
#include <stdlib.h>

void printVector(char* fname, double* vec, int n){

  FILE *f = fopen(fname, "w");
  int nn;

  if(f == NULL){
    fprintf(stderr, "Error opening %s\n", fname);
    exit(-1);
  }

  for(nn = 0; nn < n; nn++){
    fprintf(f, "%lf\n", vec[nn]);
  }

  fclose(f);
}
