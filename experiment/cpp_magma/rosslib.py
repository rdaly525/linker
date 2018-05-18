import magma
import coreir

@coreir.type_gen
def counter_type_gen(context, values):
    width = values['width'].value
    has_en = values['has_en'].value
    typ = {
        "clk": context.named_types[("coreir", "clkIn")],
        "in": context.Array(width, context.BitIn()),
        "out": context.Array(width, context.Bit())
    }
    if has_en:
        typ["en"] = context.BitIn()
    return context.Record(typ)

@coreir.generator_
def counter(context, values, module_def):
    # width = values['width'].value
    # doubleT = magma.Bits(width)
    # double = magma.DefineCircuit("double", "I", magma.In(doubleT), "O", magma.Out(doubleT))
    # shift_amount = 2
    # output = magma.concat(double.I[shift_amount:width], magma.bits(0, shift_amount))
    # magma.wire(output, double.O)
    # magma.backend.coreir_.CoreIRBackend(context).compile_definition_to_module_definition(double, module_def)
    raise NotImplemented()
