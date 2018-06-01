import os
os.environ["MANTLE_TARGET"] = "coreir"
import magma as m
from mantle.util.compressor.pop import DefinePopCount
import coreir
import mantle
import math
from magma.bitutils import log2

@coreir.type_gen
def PopCount_typegen(context, values):
    width = values['width'].value
    typ = {
        "I": context.Array(width, context.BitIn()),
        "O": context.Array(log2(width) + 1, context.Bit())
    }
    return context.Record(typ)

@coreir.generator_
def PopCount(context, values, module_def):
    print("Running magma generator")

    PopCount = DefinePopCount(values['width'].value)
    import magma.backend.coreir_ as coreir_backend
    coreir_backend.CoreIRBackend(context).compile_dependencies(PopCount)
    coreir_backend.CoreIRBackend(context).compile_definition_to_module_definition(PopCount, module_def)
