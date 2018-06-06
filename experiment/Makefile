
all: test

clean:
	$(MAKE) -C cpp_cpp clean
	$(MAKE) -C cpp_magma clean
	$(MAKE) -C cpp_magma_popcount clean
	$(MAKE) -C magma_cpp clean
	$(MAKE) -C verilog_magma_cpp clean
	$(MAKE) -C verilog_cpp clean
	$(MAKE) -C verilog_cpp_counters clean
	$(MAKE) -C verilog_magma clean

test:
	$(MAKE) -C cpp_cpp
	$(MAKE) -C cpp_magma
	$(MAKE) -C cpp_magma_popcount
	$(MAKE) -C magma_cpp
	$(MAKE) -C verilog_magma_cpp
	$(MAKE) -C verilog_cpp
	$(MAKE) -C verilog_cpp_counters
	$(MAKE) -C verilog_magma
