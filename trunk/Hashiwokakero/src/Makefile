CFLAGS   = -Wall -Wextra -std=gnu99 -g
LDFLAGS  = -lm

BIN      = hashiwokakero
FILES	 = hashiwokakero.c island.c tools.c processing.c

.PHONY: all clean cleanall

all: $(BIN)

hashiwokakero:
	$(CC) $(CFLAGS) $(LDFLAGS) $(FILES) -o $(BIN)

clean:
	@(rm -f *.o *~)

cleanall: clean
	@(rm -f *.grid $(BIN))

testsolve:
	./hashiwokakero -f ../test/test_6x6_easy_v2.txt
	./hashiwokakero -f ../test/test_6x6_easy_v3.txt
	./hashiwokakero -f ../test/test_10x10_hard.txt
	./hashiwokakero -f ../test/test_10x10_very_hard.txt
	./hashiwokakero -f ../test/test_15x15_hard.txt
	./hashiwokakero -f ../test/test_25x25_easy.txt
	./hashiwokakero -f ../test/test_25x25_easy_v2.txt
	./hashiwokakero -f ../test/test_25x25_hard.txt

testgen:
	./hashiwokakero -g -s 4 -i 4 -d ../test/generated/test_4_4.txt
	./hashiwokakero -g -s 8 -i 4 -d ../test/generated/test_8_4.txt
	./hashiwokakero -g -s 10 -i 23 -d ../test/generated/test_10_23.txt

testboth:
	./hashiwokakero -g -s 4 -i 4 -d ../test/generated/test_gensolve.txt -f ../test/generated/test_gensolve.txt

testgengraph:
	time ./hashiwokakero -g -s 255 -i 1 -d test
	time ./hashiwokakero -g -s 255 -i 100 -d test 
	time ./hashiwokakero -g -s 255 -i 200 -d test
	time ./hashiwokakero -g -s 255 -i 300 -d test
	time ./hashiwokakero -g -s 255 -i 400 -d test
	time ./hashiwokakero -g -s 255 -i 500 -d test
	time ./hashiwokakero -g -s 255 -i 600 -d test
	time ./hashiwokakero -g -s 255 -i 700 -d test
	time ./hashiwokakero -g -s 255 -i 800 -d test
	time ./hashiwokakero -g -s 255 -i 900 -d test
	time ./hashiwokakero -g -s 255 -i 1000 -d test
	time ./hashiwokakero -g -s 255 -i 2000 -d test
	time ./hashiwokakero -g -s 255 -i 3000 -d test
	time ./hashiwokakero -g -s 255 -i 4000 -d test
	time ./hashiwokakero -g -s 255 -i 5000 -d test
	time ./hashiwokakero -g -s 255 -i 6000 -d test
	time ./hashiwokakero -g -s 255 -i 8000 -d test
	time ./hashiwokakero -g -s 255 -i 10000 -d test
	
