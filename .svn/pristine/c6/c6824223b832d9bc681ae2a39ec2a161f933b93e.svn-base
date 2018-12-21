CC	 = gcc
CFLAGS   = -Wall -Wextra -std=c99
LDFLAGS  = -lm

BIN      = hashiwokakero
FILES	 = hashiwokakero.c

.PHONY: all clean cleanall $(BIN)

all: $(BIN)

hashiwokakero:
	$(CC) $(CFLAGS) $(LDFLAGS) $(FILES) -o $(BIN)

clean:
	@(rm -f *.o *~)

cleanall: clean
	@(rm -f *.grid $(BIN))
