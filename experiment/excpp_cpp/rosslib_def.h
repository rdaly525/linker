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

  counter->setGeneratorDefFromFun([](Context* c, Values genargs, ModuleDef* def) {
    uint width = genargs.at("width")->get<int>();
    bool has_en = genargs.at("has_en")->get<bool>();
    Values widthParams({{"width",Const::make(c,width)}});
    
    def->addInstance("r","mantle.reg",{{"width",Const::make(c,width)},{"has_en",Const::make(c,has_en)}},{{"init",Const::make(c,width,0)}});
    
    def->connect("self.clk","r.clk");
    
    if (has_en) {
      def->connect("self.en","r.en");
    }
    def->addInstance("c1","coreir.const",widthParams,{{"value",Const::make(c,width,1)}});
    def->addInstance("add","coreir.add",widthParams);
    def->connect("r.out","add.in0");
    def->connect("c1.out","add.in1");
    def->connect("r.out","self.out");
    def->connect("add.out","r.in");
  });
  cout << counter->toString() << endl;
  cout << "hasdef:" << counter->hasDef() << endl;
}
