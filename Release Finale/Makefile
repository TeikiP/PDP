BIN	= hashiwokakero inshiNoHeya

.PHONY: all clean cleanall

all: $(BIN)

hashiwokakero:
	make -C Hashiwokakero/src

hashitest:
	make test -C Hashiwokakero/src

inshiNoHeya:
	make -C InshiNoHeya/src

cleanall:
	make cleanall -C Hashiwokakero/src
	make cleanall -C InshiNoHeya/src
