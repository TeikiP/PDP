CFLAGS   = -Wall -Wextra -std=gnu99
LDFLAGS  = -lm

DBGFLAGS = -g
SANFLAGS = -fsanitize=address -fsanitize=leak -fsanitize=undefined
GPRFLAGS = -pg -no-pie

BIN      = inshiNoHeya
FILES    = composites.c bitset.c inshiNoHeya.c

.PHONY: all clean cleanall test

all: $(BIN)

inshiNoHeya: $(FILES)
	$(CC) $(CFLAGS) $(FILES) $(LDFLAGS) -o $(BIN)

test: $(BIN)
	@(./$(BIN) ../test/3x3_FirstLine -o tmp)
	@(./$(BIN) ../test/3x3_Generated -o tmp)
	@(./$(BIN) ../test/3x3_Spacing -o tmp)
	@(./$(BIN) ../test/4x4_Singles -o tmp)
	@(./$(BIN) ../test/5x5_Columns -o tmp)
	@(./$(BIN) ../test/5x5_Rows -o tmp)
	@(./$(BIN) ../test/5x5_Rapport -o tmp)
	@(./$(BIN) ../test/5x5_Wikipedia -o tmp)
	@(./$(BIN) ../test/6x6_Linear -o tmp)
	@(./$(BIN) ../test/8x8_Generated -o tmp)
	@(./$(BIN) ../test/16x16_Linear -o tmp)
	@(./$(BIN) ../test/16x16_Generated -o tmp)
	@(./$(BIN) ../test/24x24_Linear -o tmp)
	@(./$(BIN) ../test/24x24_Generated -o tmp)
	@(./$(BIN) ../test/32x32_Linear -o tmp)
	@(rm tmp)

test_invalid: $(BIN)
	@(./$(BIN) ../test/2x2_Invalid)
	@(./$(BIN) ../test/3x3_Invalid)
	@(./$(BIN) ../test/4x4_Invalid)
	@(./$(BIN) ../test/5x5_Invalid)
	@(./$(BIN) ../test/6x6_Invalid)
	@(./$(BIN) ../test/7x7_Invalid)
	@(./$(BIN) ../test/16x16_Invalid)

test_generate: $(BIN)
	@(./$(BIN) -g 4 -i tmp_input)
	@(./$(BIN) tmp_input -o tmp_output)
	@(./$(BIN) -g 16 -l -i tmp_input)
	@(./$(BIN) tmp_input -o tmp_output)
	@(./$(BIN) -g 8 -i tmp_input)
	@(./$(BIN) tmp_input -o tmp_output)
	@(./$(BIN) -g 3 -s -i tmp_input)
	@(./$(BIN) tmp_input -o tmp_output)
	@(rm tmp_input)
	@(rm tmp_output)

debug: $(FILES)
	$(CC) $(CFLAGS) $(DBGFLAGS) $(FILES) $(LDFLAGS) -o $(BIN)

sanitize: $(FILES)
	$(CC) $(CFLAGS) $(SANFLAGS) $(FILES) $(LDFLAGS) -o $(BIN)

gprof: $(FILES)
	$(CC) $(CFLAGS) $(GPRFLAGS) $(FILES) $(LDFLAGS) -o $(BIN)

clean:
	@(rm -f *.o *~)

cleanall: clean
	@(rm -f *.grid $(BIN))
