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

  int c, index, argCount, meanSocks, stdSocks, uniqueCount, pairedCount;
  char *pairType = malloc(10);
  char *tmp = malloc(10);
  argCount = 0;
  // defaults
  meanSocks = 30;
  uniqueCount = 11;
  pairedCount = 0;

// I/O for all variables: sample counts 1 & 2, sample size, 
  // sock prior, pair prior

	// -u unique socks
	// -p paired socks
	// -m mean socks
	// -s std socks
	// -n number of pairs (small, large)

  while ((c = getopt (argc, argv, "u:p:m:s:n:")) != -1)
    switch (c)
      {
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
	printf("mean = %d, std = %d, size = %s\n", meanSocks, stdSocks, pairType);


     for (index = optind; index < argc - 1; index+2){
        uniqueCount = atoi(argv[index]);
	pairedCount = atoi(argv[index + 1]);
        printf ("Non-option argument %s\n", argv[index]);
     }

  // build prior params from inputs


  // call sock_sim(...) in parallel, returns BigVector of matrix
  // which has n_socks, n_odd, n_pairs, prop_pairs, logical_flag


  // loop over BV, add good data to file


  // get median estimates



  return(0);
}
