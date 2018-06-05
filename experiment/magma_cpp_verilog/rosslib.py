import magma as m
import coreir


@coreir.type_gen
def LinkerTest_typegen(context, values):
    width = values['width'].value
    typ = {
        "I0": context.Array(width, context.BitIn()),
        "I1": context.Array(width, context.BitIn()),
        "O": context.Array(width, context.Bit())
    }
    return context.Record(typ)

@coreir.generator_
def LinkerTest(context, values, module_def):
    import magma.backend.coreir_ as coreir_backend
    DefineSmax = m.DeclareCoreIRGenerator(lib="commonlib", name="smax", backend=coreir_backend.CoreIRBackend(context))
    print("Running magma generator")
    width = values['width'].value
    class _LinkerTest(m.Circuit):
        name = f"LinkerTest{width}"
        IO = ["I0", m.In(m.Bits(width)), "I1", m.In(m.Bits(width)), "O", m.Out(m.Bits(width))]
        @classmethod
        def definition(self):
            Smax = DefineSmax(width=width)
            print("Hello")
            smax = Smax()
            m.wire(self.I0, smax.in0)
            m.wire(self.I1, smax.in1)
            m.wire(self.O, smax.out)
    coreir_backend.CoreIRBackend(context).compile_dependencies(_LinkerTest)
    coreir_backend.CoreIRBackend(context).compile_definition_to_module_definition(_LinkerTest, module_def)
