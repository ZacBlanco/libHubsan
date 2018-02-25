CC=gcc
CXX=g++
LIBS=bcm2835

all: spi_test spi.a spi.so libhubsan.so

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
	mv src/spi.a bin/

spi.so: spi.o
	cd src && $(CC) -shared -o spi.so -Wl,--whole-archive -lbcm2835 -Wl,--no-whole-archive spi.o
	mv src/spi.so bin/

libhubsan.so: spi.o libHubsan.o libA7105.o
	cd src && $(CC) -shared -o libhubsan.so -Wl,--whole-archive -lbcm2835 -Wl,--no-whole-archive spi.o libHubsan.o libA7105.o
	mv src/libhubsan.so bin/

spi_test: bin test.o libHubsan.o libA7105.o spi.o
	cd src && $(CC) test.o libHubsan.o libA7105.o spi.o -o spi_test -l$(LIBS)
	mv src/spi_test bin/


libHubsan.o:
	cd src && $(CC) -Wall -fPIC -c libHubsan.c

libA7105.o:
	cd src && $(CC) -Wall -fPIC -c libA7105.c

test.o:
	cd src && $(CC) -Wall -fPIC -c test.c

spi.o:
	cd src && $(CC) -Wall -fPIC -c spi.c
