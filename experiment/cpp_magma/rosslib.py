import magma as m
import coreir
import mantle

@coreir.type_gen
def counter_type_gen(context, values):
    width = values['width'].value
    has_en = values['has_en'].value
    typ = {
        "clk": context.named_types[("coreir", "clkIn")],
        "out": context.Array(width, context.Bit())
    }
    if has_en:
        typ["en"] = context.BitIn()
    return context.Record(typ)

@coreir.generator_
def counter(context, values, module_def):
    print("Running magma generator")
    width = values['width'].value
    has_en = values['has_en'].value

    IO_ = ["out", m.Out(m.Bits(width)), "clk", m.In(m.Clock)]
    if has_en:
        IO_ += ["en", m.In(m.Bit)]
    class MyCounter(m.Circuit):
        name = f"MyCounter_{width}_{has_en}"
        IO = IO_
        @classmethod
        def definition(cls):
            counter = mantle.Counter(width, has_ce=has_en)
            m.wire(counter.O, cls.out)
            m.wire(counter.CLK, cls.clk)
            if has_en:
                m.wire(counter.CE, cls.en)
    import magma.backend.coreir_ as coreir_backend
    coreir_backend.CoreIRBackend(context).compile_dependencies(MyCounter)
    coreir_backend.CoreIRBackend(context).compile_definition_to_module_definition(MyCounter, module_def)
