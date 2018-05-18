#include "coreir/coreir-python.hpp"
#include "rosslib_dec.h"

using namespace CoreIR;

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
  return rosslib;
}

COREIR_GEN_EXTERNAL_API_FOR_LIBRARY(rosslib)
