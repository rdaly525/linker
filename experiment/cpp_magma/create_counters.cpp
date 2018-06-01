#include "coreir.h"

using namespace std;
using namespace CoreIR;

//Making a slow counter.

int main() {

  Context* c = newContext();
  Namespace* g = c->getGlobal();

  //Load rosslib
  auto libman = c->getLibraryManager();
  libman->addSearchPath("/Users/rdaly/linker/experiment/cpp_magma");
  libman->loadLib("rosslib");

  // Define the slow counter
  Type* topType = c->Record({
    {"clk",c->Named("coreir.clkIn")},
    {"out",c->Bit()->Arr(16)}
  });

  Module* top = g->newModuleDecl("top",topType);
  ModuleDef* def = top->newModuleDef();
  {
    def->addInstance("count_fast","rosslib.counter",{{"width",Const::make(c,23)},{"has_en",Const::make(c,false)}});
    def->addInstance("count_slow","rosslib.counter",{{"width",Const::make(c,16)},{"has_en",Const::make(c,true)}});
    def->addInstance("eq0","coreir.eq",{{"width",Const::make(c,23)}});
    def->addInstance("c0","coreir.const",{{"width",Const::make(c,23)}},{{"value",Const::make(c,23,0)}});

    def->connect("self.clk","count_fast.clk");
    def->connect("self.clk","count_slow.clk");
    def->connect("count_slow.out","self.out");
    def->connect("c0.out","eq0.in0");
    def->connect("count_fast.out","eq0.in1");
    def->connect("eq0.out","count_slow.en");
  }
  top->setDef(def);
  c->setTop(top);

  c->runPasses({"rungenerators"});
  c->runPasses({"packbitconstants","packconnections"});
  if (!saveToFile(c,"counters.json")) {
    cout << "Save to file Failed!!!";
    exit(1);
  }

  deleteContext(c);
}
