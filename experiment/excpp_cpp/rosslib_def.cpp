#include <cassert>
#include <string>
#include <iostream>

#include "coreir.h"

#include "rosslib_def.h"

#include "rosslib_dec.h"

using namespace CoreIR;
using namespace std;

int main(int argc, char* argv[]) {
  assert(argc==3);
  string file_in = string(argv[1]);
  string file_out = string(argv[2]);
  
  Context* c = newContext();

  //Load the declaration again
  //CoreIRLoadLibrary_rosslib(c);
  c->getNamespace("rosslib")->print();
  Module* top = nullptr;
  if (!loadFromFile(c,file_in,&top)) {
    cout << "Cannot load file!!:" << file_in << endl;
    c->die();
  }
  cout << "loaded file!" << endl;
  CoreIRLoadDefinition_rosslib(c);
  
  c->runPassesOnAll({"rungenerators"});
  c->runPassesOnAll({"cullgraph"});
  
  if (!saveToFile(c,file_out)) {
    cout << "Save to file Failed!!!";
    c->die();
  }

  return 0;
}

