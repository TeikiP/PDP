BIN 	= inshiNoHeya

.PHONY: all clean cleanall test

all: $(BIN)

inshiNoHeya:
	make -C src
	@(cp src/$(BIN) .)

test:
	make test -C src
	@(cp src/$(BIN) .)

invalid:
	make invalid -C src
	@(cp src/$(BIN) .)

debug:
	make debug -C src
	@(cp src/$(BIN) .)

sanitize:
	make sanitize -C src
	@(cp src/$(BIN) .)

gprof:
	make gprof -C src
	@(cp src/$(BIN) .)

clean:
	make clean -C src
	@(rm -f *.o *~)

cleanall: clean
	make cleanall -C src
	@(rm -f *.grid $(BIN))
