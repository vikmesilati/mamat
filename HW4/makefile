CC=gcc
CCLINK=$(CC)
CFLAGS=-g -Wall -std=c99
OBJS=grades.o
EXEC=prog.exe
RM=rm -rf *.o libgrades.so
LOBJS=linked-list.o


all:  libgrades.so
#COMBLIITION RUKLES
libgrades.so: grades.o
	$(CCLINK) -shared grades.o -o libgrades.so -llinked-list -L.
grades.o: grades.c grades.h linked-list.h
	$(CC) -c -fpic grades.c

#clean objects
clean:
	$(RM)

