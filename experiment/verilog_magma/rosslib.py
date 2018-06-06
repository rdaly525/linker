import os
os.environ["MANTLE_TARGET"] = "coreir"
import magma as m
import coreir
import mantle
from mantle import XOr, Or, And
import math
from magma.bitutils import log2

from magma import Circuit, Bits, In, Out, bits, wire, cache_definition
from magma import fork, cache_definition, DefineCircuit, EndDefine, In, Out, Bit, wire
from magma.bitutils import log2

@cache_definition
def Define3to2Op():
    Op = DefineCircuit("Op", "I0", In(Bit), "I1", In(Bit), "I2", In(Bit), "O", Out(Bit))
    a = And(2)(Op.I0, Op.I1)
    b = And(2)(Op.I1, Op.I2)
    c = And(2)(Op.I2, Op.I0)
    d = Or(3)(a, b, c)
    wire(d, Op.O)
    EndDefine()
    return Op

def compress3to2():
    global n3to2s
    n3to2s = n3to2s + 1
    Op = Define3to2Op()
    return fork([XOr(3), Op()])

# compress 2 and 3 bit groups in a column
def compresscolumn2(bits):
    n = len(bits)
    ones = []
    twos = []
    for i in range(0,n,3):
        if i+1 < n:
            c = compress3to2()
            c(bits[i], bits[i+1], 0 if i+2 >= n else bits[i+2])
            ones.append(c.O[0])
            twos.append(c.O[1])
        else:
            while i < n:
                ones.append(bits[i])
                i += 1
            break
    return twos, ones

# compress only 3 bit groups in a column
def compresscolumn3(bits):
    n = len(bits)
    ones = []
    twos = []
    for i in range(0,n,3):
        if i+2 < n:
            c = compress3to2()
            c(bits[i], bits[i+1], bits[i+2])
            ones.append(c.O[0])
            twos.append(c.O[1])
        else:
            while i < n:
                ones.append(bits[i])
                i += 1
            break
    return twos, ones


# compress only 3 bit groups in a column without ripple
def compress3(bits):
    res = []
    lasttwos = []
    for b in bits:
        twos, ones = compresscolumn3(b)
        res.append(ones + lasttwos)
        lasttwos = twos
    if len(lasttwos) > 0:
        res.append(lasttwos)
    return res

# ripple adder - assumes all the columns have at most 2 bits
def ripple(bits):
    res = []
    twos = []
    for b in bits:
        # ripple: combine last column of twos with this column
        b = b + twos
        # should only require fulladders (compress 3 to 2)
        assert len(b) <= 3
        twos, ones = compresscolumn2(b)
        res.append(ones)
    if len(twos) > 0:
        res.append(twos)
    return res


# returns True if there are any columns with more than 2 bits
def iscompressible(bits):
    for b in bits:
         if len(b) > 2:
             return True
    return False

def compressor(r):
    global n2to2s, n3to2s
    n3to2s = 0
    n2to2s = 0
    while iscompressible(r):
        r = compress3(r)
    r = ripple(r)
    return sum(r, [])


@cache_definition
def DefinePopCount(n):
    class _PopCount(Circuit):
        name = 'PopCount{}'.format(n)
        IO = ['I', In(Bits(n)), 'O', Out(Bits(log2(n)+1))]
        @classmethod
        def definition(io):
            r = compressor([io.I.as_list()])
            wire( bits(r), io.O )
    return _PopCount

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
