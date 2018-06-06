CXX = g++ -std=c++11

all: unresolved.json

#------------------------------------------------------------#
#Compiling the top creation script
#------------------------------------------------------------#
create_counters.o: create_counters.cpp rosslib_dec.h
	$(CXX) -c create_counters.cpp -o create_counters.o

create_counters: create_counters.o rosslib_dec.o
	$(CXX) rosslib_dec.o create_counters.o -lcoreir -o create_counters

#------------------------------------------------------------#
#Creating the rosslib library
#------------------------------------------------------------#
rosslib_dec.o: rosslib_dec.cpp rosslib_dec.h
	$(CXX) -c rosslib_dec.cpp -o rosslib_dec.o

libcoreir-rosslib.dylib: rosslib_dec.o
	$(CXX) rosslib_dec.o -install_name "@rpath/libcoreir-rosslib.dylib" -dynamiclib -lcoreir -o libcoreir-rosslib.dylib

#------------------------------------------------------------#
#Actual project flow
#------------------------------------------------------------#
#'compile' the counters.json
counters.json: create_counters
	./create_counters

#output all the unresolved symbols
unresolved.json: counters.json
	coreir -i counters.json -p cullgraph,unresolved -a -o unresolved.json

##Pass in all the unresolved symbols to the definition exe
#resolved.json: unresolved.json
#	./rosslib_def unresolved.json resolved.json
#
##Does not actually work yet. TODO
#merged.json: counters.json resolved.json
#	coreir -i counters.json,resolved.json -o merged.json 

clean:
	-rm *.json
	-rm *.o
	-rm *.dylib
	-rm create_counters
	-rm rosslib_def
