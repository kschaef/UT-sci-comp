#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_statistics_double.h>

int main(int argc, char *argv[]){

  int c, index, argCount, meanSocks, stdSocks, uniqueCount, pairedCount, nbR;
  float alpha, beta, nbP;
  char *pairType = malloc(10);
  char *tmp = malloc(10);
  argCount = 0;
  // defaults
  meanSocks = 30;
  uniqueCount = 11;
  pairedCount = 0;
  pairType = "large";

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
  nbP = meanSocks / (stdSocks * stdSocks);
  nbR = meanSocks * nbP / (1. - nbP);  // parameters for gsl are P and R - 1

  if(strcmp(pairType, "small") == 0){
    alpha = 15; // CI (.7, .98), median = .9 
  } else {
    alpha = 30; // CI (.8, .99(, median = .95
  }
  beta = 2;

  // call sock_sim(...) in parallel, returns BigVector of matrix
  // which has n_socks, n_odd, n_pairs, prop_pairs, logical_flag


  // loop over BV, add good data to file


  // get median estimates



  return(0);
}
