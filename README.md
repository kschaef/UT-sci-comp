## Approximate Bayesian Computation for Tiny Data

This program runs the ABC algorithm for an example situation with Tiny Data: estimating the number of socks given a small sample. 

Before running the Makefile, please be sure to load both the gsl and 
Python 2.7.3 modules. This can be done with `module load gsl` and 
`module load python/2.7.3-epd-7.3.2`, respectively. You will also need to 
have enabled X11 forwarding in order to generate and view the plots.  

A default case will be run simply calling the executable `bin/abc.exe` after calling `make` from the main project folder.

Calling `bin/abc.exe -h` will describe the options available for running your own case. These options are also described here for convenience:

options:

-u: count of unique socks

-p: count of paired socks (e.g. 1 pair = 2 socks)

-m: estimated amount of total socks

-s: error for total socks estimate (default is m / 2)

-n: 'small' or 'large' for proportion of paired socks

You can get plots of the posterior distributions for unique (odd) socks, paired socks, total socks, and proportion of paired socks by calling `make plots` after running abc.exe with your options. If you would like the plots for the default case, you can simply run `make default_plots` which will call abc.exe for you.

The .png for these plots, along with the data files for creating the plots, 
will be stored in the `bin` folder with the executable. 

If you would like to run the code in parallel, simply call `make parallel`, 
which will generate `bin/abc_parallel.exe` for you. The options are the same
as in the serial case. However, you need to set the number of threads with
`export OMP_NUM_THREADS=3` or however many threads you would like.

  
