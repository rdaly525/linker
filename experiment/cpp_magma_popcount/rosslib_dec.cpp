#include "coreir/coreir-python.hpp"
#include "rosslib_dec.h"

using namespace CoreIR;
using namespace std;

COREIR_GEN_C_API_DEFINITION_FOR_LIBRARY(rosslib);


Namespace* CoreIRLoadLibrary_rosslib(Context* c) {

  pythonInitialize();
  Namespace* rosslib = c->newNamespace("rosslib");

  Params popCountParams({
    {"width", c->Int()},
  });

  TypeGen* popCountType = TypeGenFromPython::make(rosslib, "popCountType", popCountParams, "rosslib", "PopCount_typegen");

  rosslib->newGeneratorDecl("PopCount", popCountType, popCountParams);

  Generator* PopCount = c->getGenerator("rosslib.PopCount");
  cout << PopCount->toString() << endl;

  PopCount->setGeneratorDefFromFun(ModuleDefGenFunFromPython("rosslib", "PopCount"));
  cout << PopCount->toString() << endl;
  cout << "hasdef:" << PopCount->hasDef() << endl;
  return rosslib;
}

COREIR_GEN_EXTERNAL_API_FOR_LIBRARY(rosslib)
