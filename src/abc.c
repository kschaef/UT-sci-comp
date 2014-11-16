#include <stdio.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_statistics_double.h>

int main(int argc, char *argv[]){

  // I/O for all variables: sample counts 1 & 2, sample size, 
  // sock prior, pair prior, processors


  // build prior params from inputs


  // call sock_sim(...) in parallel, returns BigVector of matrix
  // which has n_socks, n_odd, n_pairs, prop_pairs, logical_flag


  // loop over BV, add good data to file


  // get median estimates



  return(0);
}
