CC=g++
LIBS=bcm2835

all: spi_test spi.a

clean:
	rm -rf *.o *.a src/*.o src/*.a  bin/

bin:
	mkdir bin
	rm -r bin
	mkdir bin

test: spi_test
	./spi_test

spi.a: spi.o
	cd src && ar rcs spi.a spi.o

spi_test: spi.o libA7105.o test.o bin
	cd src && $(CC) test.o spi.o libA7105.o -o spi_test -l$(LIBS)
	#$(CC) -Wall -l$(LIBS) spi.a test.o
	mv src/spi_test bin/
	
libA7105.o:
	cd src && $(CC) -Wall -c libA7105.cpp

test.o:
	cd src && $(CC) -Wall -c test.c

spi.o:
	cd src && $(CC) -Wall -c -lbcm2835 spi.c
