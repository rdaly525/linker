#include "coreir.h"
#include "rosslib_dec.h"

using namespace std;
using namespace CoreIR;

//Making a slow counter.

int main() {

  Context* c = newContext();
  Namespace* g = c->getGlobal();

  //This is the "header" file include
  CoreIRLoadLibrary_rosslib(c);

  Type* topType = c->Record({
    {"I",c->BitIn()->Arr(16)},
    {"O",c->Bit()->Arr(5)}
  });

  Module* top = g->newModuleDecl("top",topType);
  ModuleDef* def = top->newModuleDef();
  {
    def->addInstance("popcount16","rosslib.PopCount",{{"width",Const::make(c,16)}});

    def->connect("self.I","popcount16.I");
    def->connect("self.O","popcount16.O");
  }
  top->setDef(def);
  c->setTop(top);

  c->runPasses({"rungenerators", "cullgraph", "printer"});
  if (!saveToFile(c,"popcount.json")) {
    cout << "Save to file Failed!!!";
    exit(1);
  }

  deleteContext(c);
}
