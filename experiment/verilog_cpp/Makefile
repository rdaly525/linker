all:
	yosys -p "write_coreir -top top" -m ./../../yosys/write_coreir.so top.v
	coreir -i top.json -l commonlib -p rungenerators,cullgraph -o top2.json -a

clean:
	rm *.json
