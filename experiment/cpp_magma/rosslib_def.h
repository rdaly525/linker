#include "coreir/coreir-python.hpp"

using namespace std;
using namespace CoreIR;
void CoreIRLoadDefinition_rosslib(Context* c) {
  Generator* counter = c->getGenerator("rosslib.counter");
  cout << counter->toString() << endl;

  cout << "sdfds" << endl;
  assert(counter->getGeneratedModules().size()>0);
  for (auto m : counter->getGeneratedModules()) {
    cout << m.second->toString() << endl;
  }

  counter->setGeneratorDefFromFun(ModuleDefGenFunFromPython("rosslib", "counter"));
  cout << counter->toString() << endl;
  cout << "hasdef:" << counter->hasDef() << endl;
}
