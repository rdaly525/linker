#include "rosslib_dec.h"

using namespace CoreIR;

COREIR_GEN_C_API_DEFINITION_FOR_LIBRARY(rosslib);

Namespace* CoreIRLoadLibrary_rosslib(Context* c) {
  Namespace* rosslib = c->newNamespace("rosslib");

  Params counterParams({
    {"width", c->Int()},
    {"has_en", c->Bool()},
  });

  TypeGen* counterType = rosslib->newTypeGen(
    "counterType", //Name of TypeGen
    counterParams, //Parameters to be passed into TypeGen
    [](Context* c, Values genargs) {
      uint width = genargs.at("width")->get<int>();
      bool has_en = genargs.at("has_en")->get<bool>();
      RecordParams ioParams({
        {"clk", c->Named("coreir.clkIn")},
        {"in", c->BitIn()->Arr(width)},
        {"out", c->Bit()->Arr(width)}
      });
      if (has_en) {
        ioParams.push_back({"en",c->BitIn()});
      }
      return c->Record(ioParams);
    }
  );

  rosslib->newGeneratorDecl("counter", counterType, counterParams);
  return rosslib;
}

COREIR_GEN_EXTERNAL_API_FOR_LIBRARY(rosslib)
