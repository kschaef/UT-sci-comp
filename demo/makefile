CC := icc
CFLAGS := #-g -O0
LDFLAGS := -I$(TACC_GSL_INC) -I$(TACC_GSL_INC)/gsl
LDLIBS := -L$(TACC_GSL_LIB) -lgsl -lgslcblas -limf -lm

proj: abc_single.o sock_sim.o helper.o
	$(CC) $^ -o $@ $(CFLAGS)  $(LDLIBS)
abc_single.o: abc_single.c helper.h
	$(CC) -c $(CFLAGS) $< $(LDFLAGS)
sock_sim.o: sock_sim.c
	$(CC) -c $(CFLAGS) $< $(LDFLAGS)
.PHONY: clean dat_clean plots
clean:
	rm *.o proj
dat_clean:
	rm *.dat

plots: hist_plots.py
	python hist_plots.py
