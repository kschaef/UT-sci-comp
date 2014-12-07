#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<omp.h>
#include<gsl/gsl_randist.h>
#include<gsl/gsl_rng.h>
gsl_rng *r; //global generator

int sock_sim(double prior_r,double prior_p,double alpha,double beta,double obs_paired,double obs_odd,double *BigVector,int iter){

 //variables, gsl rng initiation
 int i,j,match_count,n_picked;
 unsigned int n_socks;
 double prop_pairs,n_pairs,n_odd,prior_n;
 double obs_total = obs_paired + obs_odd;
 prior_n = prior_r - 1;
 match_count = 0; 

 double temp_paired,temp_odd,temp_pairs;

 //setup gsl random seed
 const gsl_rng_type * T;
 gsl_rng_env_setup();

 T = gsl_rng_default;
 r = gsl_rng_alloc(T); 

 
 for(i=0;i<iter;i++){  


   //sample, get n_pairs and n_odd
   n_socks = gsl_ran_negative_binomial(r,prior_p,prior_n);
   prop_pairs = gsl_ran_beta(r,alpha,beta);
   //n_pairs = floor(.5*(n_socks*prop_pairs));
   n_pairs = round(floor(.5*n_socks)*prop_pairs);
   n_odd = n_socks - 2*n_pairs;

   //make generated population
   double *gen_pop = (double *)malloc(sizeof(double)*n_socks);
   //double gen_pop[(int) n_socks];
   for(j=0;j<n_pairs;j++){

     gen_pop[2*j] = (double) j;
     gen_pop[(2*j)+1] = (double) j;

   }
   for(j=2*n_pairs;j<n_socks;j++){

     gen_pop[j]= (double) j;

   }

   //get generated sample size
   if(obs_total <= n_socks){

     n_picked = (int) obs_total;

   }else{ n_picked = n_socks; }


   //get sample vector
   double *gen_samp = (double *)malloc(sizeof(double)*n_picked);

   //count pairs

   //sample from generated population
   gsl_ran_choose(r,gen_samp,n_picked,gen_pop,n_socks,sizeof(double));
 
   //sort sample
   gsl_sort(gen_samp,1,n_picked);

   //count the number of pairs/odd in sample
   temp_pairs = 0.;
   temp_odd = 1.;
   for(j=1;j<n_picked;j++){

     if(gen_samp[j] == gen_samp[j-1]){

       temp_pairs = temp_pairs + 1;
       temp_odd = temp_odd - 1;
       continue;

     }else{ temp_odd = temp_odd + 1; }

   }
   temp_paired = 2*temp_pairs;


   //allocate big vector
   BigVector[5*i] = (double) n_socks;
   BigVector[(5*i) + 1] = n_pairs;
   BigVector[(5*i) + 2] = n_odd;
   BigVector[(5*i) + 3] = prop_pairs;

   //counter
   if(temp_odd==obs_odd && temp_paired==obs_paired){ 

       match_count = match_count + 1;
       BigVector[(5*i) + 4] = 1.;
       continue;
 
   }
   else{
   
      BigVector[(5*i) + 4] = 0.;
      continue;
  
    }

   //free the temp allocated things
   free(gen_pop);
   free(gen_samp);
 }

 gsl_rng_free(r);
 return(match_count);

}
