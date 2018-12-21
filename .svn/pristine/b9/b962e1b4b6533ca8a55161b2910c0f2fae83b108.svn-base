CPPFLAGS = -I. 
CFLAGS   = -Wall -Wextra -std=c99
LDFLAGS  = -lm

hashiwokakero:
	make -C Hashiwokakero/src

inshiNoHeya:
	make -C InshiNoHeya/src

.PHONY: clean cleanall

all: hashiwokakero inshiNoHeya

cleanall:
	make cleanall -C Hashiwokakero/src
	make cleanall -C InshiNoHeya/src


