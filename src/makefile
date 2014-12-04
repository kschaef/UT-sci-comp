CC := icc
CFLAGS := -O0 -openmp
LDFLAGS := -I$(TACC_GSL_INC) -I$(TACC_GSL_INC)/gsl
LDLIBS := -L$(TACC_GSL_LIB) -lgsl -lgslcblas -limf -lm

proj: abc_single.o sock_sim.o helper.o
	$(CC) abc_single.o sock_sim.o helper.o -o proj $(CFLAGS)  $(LDLIBS)
abc_single.o: abc_single.c
	$(CC) -c $(CFLAGS) abc_single.c $(LDFLAGS)
sock_sim.o: sock_sim.c
	$(CC) -c $(CFLAGS) sock_sim.c $(LDFLAGS)
helper.o: helper.c
	$(CC) -c $(CFLAGS) helper.c $(LDFLAGS)
.PHONY: clean
clean:
	rm *.o proj
dat_clean:
	rm *.dat
