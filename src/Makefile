# Files
SRC := $(wildcard *.c)
OBJ := $(patsubst %.c, %.o, $(SRC))

# Options
CC := mpicc
CFLAGS := -O3 -I$(TACC_GSL_INC) -I$(TACC_GSL_INC)/gsl
LDFLAGS := -L/lib -L$(TACC_GSL_LIB)
LDLIBS := -limf -lm -lgsl -lgslcblas

# Rules
abc.exe: abc.o helper.o 
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)
abc.o: abc.c helper.h
	$(CC) $(CFLAGS) -c $<
helper.o: helper.c helper.h
	$(CC) $(CFLAGS) -c $<

.PHONY: plots default_plots clean

plots: hist_plots.py
	python hist_plots.py

default_plots: abc.exe hist_plots.py
	./abc.exe
	python hist_plots.py
clean:
	rm *.o abc.exe
