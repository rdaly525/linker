CXX = g++ -std=c++11

all: resolved.json

#------------------------------------------------------------#
#Creating the rosslib definition executable 
#------------------------------------------------------------#
rosslib_def.o: rosslib_def.h rosslib_def.cpp rosslib_dec.h
	$(CXX) -c rosslib_def.cpp -o rosslib_def.o

rosslib_def: rosslib_def.o rosslib_dec.o
	$(CXX) rosslib_def.o rosslib_dec.o -lcoreir -o rosslib_def


#------------------------------------------------------------#
#Actual project flow
#------------------------------------------------------------#
#'compile' the counters.json
main.json: test.py
	python test.py -o main.json

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
