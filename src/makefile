CC := icc
LDFLAGS := -I$TACC_GSL_INC -I$TACC_GSL_INC/gsl
LDLIBS := -L$TACC_GSL_LIB -lgsl -lgslcblas -limf -lm

proj: abc_single.o sock_sim.o helper.o
	$(CC) proj abc_single.o sock_sim.o $(LDLIBS)
abc_single.o: abc_single.c
	$(CC) -c abc_single.c $(LDFLAGS)
sock_sim.o: sock_sim.c
	$(CC) -c sock_sim.c $(LDFLAGS)
helper.o: helper.c
	$(CC) -c helper.o $(LDFLAGS)
.PHONY: clean
clean:
	rm *.o
dat_clean:
	rm *.dat
