CXX = g++ -std=c++11

LDFLAGS = -lcoreir -lcoreir-python

PYTHON_CONFIG ?= python3-config
PYTHON_PREFIX=$(shell $(PYTHON_CONFIG) --prefix)
PYTHONHOME ?= $(PYTHON_PREFIX)
override CXXFLAGS += $(shell $(PYTHON_CONFIG) --includes) -DPYTHON_HOME="L\"$(PYTHONHOME)\"" -DPYTHON_EXECUTABLE="L\"$(shell which python)\""
PYTHON_LIBS = $(PYTHON_PREFIX)/lib
override LDFLAGS += -L $(PYTHON_LIBS) $(shell $(PYTHON_CONFIG) --libs)
DYLDFLAGS = -Wl,-rpath,$(PYTHON_LIBS)

all: libcoreir-rosslib.dylib top.json

#------------------------------------------------------------#
#Creating the rosslib library
#------------------------------------------------------------#
rosslib_dec.o: rosslib_dec.cpp rosslib_dec.h
	$(CXX) $(CXXFLAGS) -c rosslib_dec.cpp -o rosslib_dec.o

libcoreir-rosslib.dylib: rosslib_dec.o
	$(CXX) $(CXXFLAGS) rosslib_dec.o -install_name "@rpath/libcoreir-rosslib.dylib" $(LDFLAGS) -dynamiclib $(DYLDFLAGS) -o libcoreir-rosslib.dylib


top.v:

#------------------------------------------------------------#
#Actual project flow
#------------------------------------------------------------#
#'compile' the counters.json
top.json: top.v
	yosys -p "write_coreir -top top" -m ./../../yosys/write_coreir.so top.v
	coreir -i top.json -l rosslib -p rungenerators -o top2.json -a

#output all the unresolved symbols
#unresolved.json: counters.json
#	coreir -i counters.json -p cullgraph,unresolved -a -o unresolved.json

clean:
	-rm *.json
	-rm *.o
	-rm *.dylib
	-rm create_popcount
	-rm rosslib_def
