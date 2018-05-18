import magma as m
import coreir
import mantle

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
    width = values['width'].value
    has_en = values['has_en'].value

    Counter = mantle.DefineCounter(width, has_en=has_en)
    magma.backend.coreir_.CoreIRBackend(context).compile_definition_to_module_definition(Counter, module_def)
