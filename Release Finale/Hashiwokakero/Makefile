BIN 	= hashiwokakero

.PHONY: all clean cleanall

all: $(BIN)

hashiwokakero:
	make -C src
	@(cp src/$(BIN) .)

testsolve:
	make testsolve -C src
	@(cp src/$(BIN) .)

testgen:
	make testgen -C src
	@(cp src/$(BIN) .)

testboth:
	make testboth -C src
	@(cp src/$(BIN) .)

testgengraph:
	make tetgengraph -C src
	@(cp src/$(BIN) .)

clean:
	make clean -C src
	@(rm -f *.o *~)

cleanall: clean
	make cleanall -C src
	@(rm -f *.grid $(BIN))
