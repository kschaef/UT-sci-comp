#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_statistics_double.h>
#include <gsl_sort_float.h>
#include "helper.h"

#define iter 4

int main(int argc, char *argv[]){

  int c, index, argCount, meanSocks, stdSocks, uniqueCount, pairedCount;
  double alpha, beta, nbP, nbR;
  char *pairType = malloc(10);
  char *tmp = malloc(10);
  argCount = 0;
  // defaults
  meanSocks = 30;
  uniqueCount = 11;
  pairedCount = 0;
  pairType = "large";


  int i, j, k;
  double *nSocks, *nPairs, *nOdd, *propPairs;
  //double BigVector[iter * 5];
  double BigVector[iter * 5] = {1, 2, 3, 4, 0, 1, 2, 3, 4, 1, 6, 7, 8, 9, 1,
    11, 12, 13, 14, 1};
  double medSocks, medPairs, medOdd, medPropPairs;

  // I/O for all variables: sample counts 1 & 2, sample size, 
  // sock prior, pair prior

	// -u unique socks
	// -p paired socks
	// -m mean socks
	// -s std socks
	// -n number of pairs (small, large)

  while ((c = getopt (argc, argv, "hu:p:m:s:n:")) != -1)
    switch (c)
      {
      case 'h':
	printf("options: \n\t-u: count of unique socks\n");
	printf("\t-p: count of paired socks (e.g. 1 pair = 2 socks)\n");
	printf("\t-m: estimated amount of total socks\n");
	printf("\t-s: error for total socks estimate (default is m / 2)\n");
	printf("\t-n: \'small\' or \'large\' for proportion of paired socks\n");
	return(0);
      case 'u':
	uniqueCount = atoi(optarg);
	break;
      case 'p':
	pairedCount = atoi(optarg);
	break;
      case 'm':
        meanSocks = atoi(optarg);
        break;
      case 's':
        stdSocks = atoi(optarg);
        break;
      case 'n':
	if (strcmp(optarg, "small") != 0 && strcmp(optarg, "large") != 0){
          fprintf(stderr, "-n requires either 'small' or 'large'\n");
          return(1);
        }
        strcpy(pairType, optarg);
        break;
      case '?':
        if (optopt == 'm' || optopt == 's' || optopt == 'p')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        return 1;
      default:
        abort ();
      }

  if (stdSocks == 0){
    stdSocks = meanSocks / 2; // integer division intentional
  }

  printf("Using: \n\t%d unique socks\n", uniqueCount);
  printf("\t%d paired socks\n", pairedCount);
  printf("\t%d estimated total socks +- %d socks\n", meanSocks, stdSocks);
  printf("\t%s proportion of paired socks\n", pairType);
  


  // build prior params from inputs
  nbP = meanSocks * 1.0  / (stdSocks * stdSocks);
  nbR = meanSocks * nbP / (1. - nbP);  // parameters for gsl are P and R - 1

  if(strcmp(pairType, "small") == 0){
    alpha = 15; // CI (.7, .98), median = .9 
  } else {
    alpha = 30; // CI (.8, .99), median = .95
  }
  beta = 2;


  // call sock_sim(...) in parallel, returns BigVector of matrix
  // which has n_socks, n_odd, n_pairs, prop_pairs, logical_flag

  // loop over BV, add good data to file

  // get size of good values
  j = 0;
  for (i = 4; i < (5 * iter); i+=5){
    if(BigVector[i] == 1){
      j++;
    }
  }

  // alloc vectors
  nSocks = (double*) malloc(j * sizeof(double));
  nPairs = (double*) malloc(j * sizeof(double));
  nOdd = (double*) malloc(j * sizeof(double));
  propPairs = (double*) malloc(j * sizeof(double));  

  // fill vectors
  k = 0;
  for(i = 0; i < (5 * iter); i+=5){
    if (BigVector[i + 4] == 1){
      nSocks[k] = BigVector[i];
      nPairs[k] = BigVector[i + 1];
      nOdd[k] = BigVector[i + 2];
      propPairs[k] = BigVector[i + 3];
      k++;
    }
  }

  // write to file
  printVector("num_socks.dat", nSocks, j);
  printVector("num_pairs.dat", nPairs, j);
  printVector("num_odd.dat", nOdd, j);
  printVector("prop_pairs.dat", propPairs, j);

  // get median estimates
  gsl_sort(nSocks, 1, j);
  gsl_sort(nPairs, 1, j);
  gsl_sort(nOdd, 1, j);
  gsl_sort(propPairs, 1, j);

  medSocks = gsl_stats_median_from_sorted_data(nSocks, 1, j);
  medPairs = gsl_stats_median_from_sorted_data(nPairs, 1, j);
  medOdd = gsl_stats_median_from_sorted_data(nOdd, 1, j);
  medPropPairs = gsl_stats_median_from_sorted_data(propPairs, 1, j);
 
  printf("\nEstimated number of socks: %d\n", (int) medSocks);
  printf("Estimated number of pairs: %d\n", (int) medPairs);
  printf("Estimated number of unmatched socks: %d\n", (int) medOdd);
  printf("Estimated proportion of paired socks: %.3lf\n", medPropPairs);


  free(nSocks); free(nPairs); free(nOdd); free(propPairs);


  return(0);
}
