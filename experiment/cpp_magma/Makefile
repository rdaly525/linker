CXX = g++ -std=c++11

LDFLAGS = -lcoreir -lcoreir-python

PYTHON_CONFIG ?= python-config
PYTHON_PREFIX=$(shell $(PYTHON_CONFIG) --prefix)
PYTHONHOME ?= $(PYTHON_PREFIX)
override CXXFLAGS += $(shell $(PYTHON_CONFIG) --includes) -DPYTHON_HOME="L\"$(PYTHONHOME)\"" -DPYTHON_EXECUTABLE="L\"$(shell which python)\""
PYTHON_LIBS = $(PYTHON_PREFIX)/lib
override LDFLAGS += -L $(PYTHON_LIBS) $(shell $(PYTHON_CONFIG) --libs)
DYLDFLAGS = -Wl,-rpath,$(PYTHON_LIBS)

all: resolved.json

#------------------------------------------------------------#
#Compiling the top creation script
#------------------------------------------------------------#
create_counters.o: create_counters.cpp rosslib_dec.h
	$(CXX) -c create_counters.cpp -o create_counters.o

create_counters: create_counters.o rosslib_dec.o
	$(CXX) rosslib_dec.o create_counters.o $(LDFLAGS) $(DYLDFLAGS) -o create_counters

#------------------------------------------------------------#
#Creating the rosslib header
#------------------------------------------------------------#
rosslib_dec.o: rosslib_dec.cpp rosslib_dec.h
	$(CXX) $(CXXFLAGS) -c rosslib_dec.cpp -o rosslib_dec.o

libcoreir-rosslib.dylib: rosslib_dec.o
	$(CXX) $(CXXFLAGS) rosslib_dec.o -install_name "@rpath/libcoreir-rosslib.dylib" $(LDFLAGS) -dynamiclib $(DYLDFLAGS) -o libcoreir-rosslib.dylib

#------------------------------------------------------------#
#Creating the rosslib definition executable
#------------------------------------------------------------#
rosslib_def.o: rosslib_def.h rosslib_def.cpp rosslib_dec.h
	$(CXX) -c rosslib_def.cpp -o rosslib_def.o

rosslib_def: rosslib_def.o rosslib_dec.o
	$(CXX) rosslib_def.o rosslib_dec.o $(LDFLAGS) -o rosslib_def


#------------------------------------------------------------#
#Actual project flow
#------------------------------------------------------------#
#'compile' the counters.json
counters.json: create_counters
	./create_counters

#output all the unresolved symbols
unresolved.json: counters.json
	coreir -i counters.json -p cullgraph,unresolved -a -o unresolved.json

#Pass in all the unresolved symbols to the definition exe
resolved.json: unresolved.json rosslib_def
	./rosslib_def unresolved.json resolved.json

#Does not actually work yet. TODO
merged.json: counters.json resolved.json
	coreir -i counters.json,resolved.json -o merged.json

clean:
	-rm *.json
	-rm *.o
	-rm *.dylib
	-rm create_counters
	-rm rosslib_def
