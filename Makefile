FLAGS= -Wall -g
CC=gcc
AR=ar

OBJECT_MAIN = StrList.o Main.o 

all: StrList libStrList.a

StrList: $(OBJECT_MAIN) libStrList.a
	$(CC) $(FLAGS) -o StrList $(OBJECT_MAIN)

StrList.o: StrList.c StrList.h
	$(CC) $(FLAGS) -c StrList.c

libStrList.a: $(OBJECT_MAIN)
	$(AR) -rcs libStrList.a $(OBJECT_MAIN)

.PHONY: clean all

clean:
	rm -f *.o StrList libStrList.a