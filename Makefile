# Files
SRC := $(wildcard *.c)
OBJ := $(patsubst %.c, %.o, $(SRC))

# Options
CC := mpicc
CFLAGS := -O3 -I$(TACC_GSL_INC) -I$(TACC_GSL_INC)/gsl
LDFLAGS := -L/lib -L$(TACC_GSL_LIB)
LDLIBS := -limf -lm -lgsl -lgslcblas

# Rules
bin/abc.exe: bin/abc.o bin/helper.o 
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)
bin/abc.o: src/abc.c src/helper.h
	$(CC) $(CFLAGS) -c $< -o $@
bin/helper.o: src/helper.c src/helper.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: plots default_plots clean

plots: src/hist_plots.py
	python src/hist_plots.py

default_plots: bin/abc.exe src/hist_plots.py
	bin/abc.exe
	python src/hist_plots.py
clean:
	rm bin/*.o bin/abc.exe
