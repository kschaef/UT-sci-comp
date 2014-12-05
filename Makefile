# Files
SRC := $(wildcard *.c)
OBJ := $(patsubst %.c, %.o, $(SRC))

# Options
CC := icc
CFLAGS := -openmp -O3 -I$(TACC_GSL_INC) -I$(TACC_GSL_INC)/gsl
LDFLAGS := -openmp -L/lib -L$(TACC_GSL_LIB)
LDLIBS := -limf -lm -lgsl -lgslcblas

# Rules
bin/abc.exe: bin/abc_single.o bin/sock_sim.o bin/helper.o 
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)
bin/sock_sim.o: src/sock_sim.c
	$(CC) $(CFLAGS) -c $< -o $@
bin/abc_single.o: src/abc_single.c src/helper.h
	$(CC) $(CFLAGS) -c $< -o $@
bin/helper.o: src/helper.c src/helper.h
	$(CC) $(CFLAGS) -c $< -o $@

parallel: bin/abc_parallel.exe

bin/abc_parallel.exe: bin/abc_parallel.o bin/sock_parallel.o bin/helper.o 
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)
bin/abc_parallel.o: src/abc_parallel.c src/helper.h
	$(CC) $(CFLAGS) -c $< -o $@
bin/sock_parallel.o: src/sock_parallel.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: plots default_plots clean dat_clean

plots: src/hist_plots.py
	python src/hist_plots.py

default_plots: bin/abc.exe src/hist_plots.py
	bin/abc.exe
	python src/hist_plots.py
clean:
	rm bin/*.o bin/abc.exe bin/abc_parallel.exe

dat_clean: 
	rm bin/*.dat
