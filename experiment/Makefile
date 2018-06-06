
all: test

clean:
	$(MAKE) -C cpp_cpp clean
	$(MAKE) -C cpp_magma clean
	$(MAKE) -C cpp_magma_popcount clean
	$(MAKE) -C magma_cpp clean
	$(MAKE) -C magma_cpp_verilog clean
	$(MAKE) -C verilog_cpp clean
	$(MAKE) -C verilog_cpp2 clean
	$(MAKE) -C verilog_magma clean

test:
	$(MAKE) -C cpp_cpp
	$(MAKE) -C cpp_magma
	$(MAKE) -C cpp_magma_popcount
	$(MAKE) -C magma_cpp
	#$(MAKE) -C magma_cpp_verilog
	$(MAKE) -C verilog_cpp
	$(MAKE) -C verilog_cpp2
	$(MAKE) -C verilog_magma
