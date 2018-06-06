#include "coreir/coreir-python.hpp"
#include "rosslib_dec.h"

using namespace CoreIR;
using namespace std;

COREIR_GEN_C_API_DEFINITION_FOR_LIBRARY(rosslib);


Namespace* CoreIRLoadLibrary_rosslib(Context* c) {

  pythonInitialize();
  Namespace* rosslib = c->newNamespace("rosslib");

  Params linkerTestParams({
    {"width", c->Int()},
  });

  TypeGen* linkerTestType = TypeGenFromPython::make(rosslib, "linkerTestType", linkerTestParams, "rosslib", "LinkerTest_typegen");

  rosslib->newGeneratorDecl("LinkerTest", linkerTestType, linkerTestParams);

  Generator* LinkerTest = c->getGenerator("rosslib.LinkerTest");
  cout << LinkerTest->toString() << endl;

  LinkerTest->setGeneratorDefFromFun(ModuleDefGenFunFromPython("rosslib", "LinkerTest"));
  cout << LinkerTest->toString() << endl;
  cout << "hasdef:" << LinkerTest->hasDef() << endl;
  return rosslib;
}

COREIR_GEN_EXTERNAL_API_FOR_LIBRARY(rosslib)
