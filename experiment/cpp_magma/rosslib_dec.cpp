#include "coreir/coreir-python.hpp"
#include "rosslib_dec.h"

using namespace CoreIR;
using namespace std;

COREIR_GEN_C_API_DEFINITION_FOR_LIBRARY(rosslib);


Namespace* CoreIRLoadLibrary_rosslib(Context* c) {

  pythonInitialize();
  Namespace* rosslib = c->newNamespace("rosslib");

  Params counterParams({
    {"width", c->Int()},
    {"has_en", c->Bool()},
  });

  TypeGen* counterType = TypeGenFromPython::make(rosslib, "counterType", counterParams, "rosslib", "counter_type_gen");

  rosslib->newGeneratorDecl("counter", counterType, counterParams);

  Generator* counter = c->getGenerator("rosslib.counter");
  cout << counter->toString() << endl;

  // assert(counter->getGeneratedModules().size()>0);
  // for (auto m : counter->getGeneratedModules()) {
  //   cout << m.second->toString() << endl;
  // }

  counter->setGeneratorDefFromFun(ModuleDefGenFunFromPython("rosslib", "counter"));
  cout << counter->toString() << endl;
  cout << "hasdef:" << counter->hasDef() << endl;
  return rosslib;
}

COREIR_GEN_EXTERNAL_API_FOR_LIBRARY(rosslib)
