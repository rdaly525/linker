import sys
import magma as m
output_file = sys.argv[1]

DefineSmax = m.DeclareCoreIRGenerator(lib="commonlib", name="smax")
width = 16

class LinkerTest(m.Circuit):
    name = "LinkerTest0"
    IO = ["I0", m.In(m.Bits(width)), "I1", m.In(m.Bits(width)), "O", m.Out(m.Bits(width))]
    @classmethod
    def definition(self):
        Smax = DefineSmax(width=width)
        smax = Smax()
        m.wire(self.I0, smax.in0)
        m.wire(self.I1, smax.in1)
        m.wire(self.O, smax.out)

m.compile(output_file, LinkerTest, output="coreir")
