CC = g++

CFLAGS = -std=c++11 -g -Wall

default: make

make: main.o generate.o historic.o
	$(CC) $(CFLAGS) -o main main.o generate.o historic.o -lm

generate.o: generate.cpp generate.hpp
	$(CC) $(CFLAGS) -c generate.cpp

historic.o: historic.cpp historic.hpp
	$(CC) $(CFLAGS) -c historic.cpp

main.o: main.cpp generate.hpp historic.hpp
	$(CC) $(CFLAGS) -c main.cpp

clean:
	$(RM) *.o *~ main historic generate
