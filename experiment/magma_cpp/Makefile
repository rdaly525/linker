CXX = g++ -std=c++11

all: libcoreir-rosslib.dylib main.json

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
main.json: test.py
	python test.py main

clean:
	-rm *.json
	-rm *.o
	-rm *.dylib
