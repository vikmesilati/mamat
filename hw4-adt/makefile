CC=gcc
CCLINK=$(CC)
CFLAGS=-g -Wall -std=c99
OBJS=grades.o
EXEC=prog.exe
RM=rm -rf *.o $(EXEC)


#THE FIRST RULE
$(EXEC): $(OBJS)
	$(CCLINK) $(OBJS) -o $(EXEC) -llinked-list -L.



#COMBLIITION RUKLES
liblinked-list.so: linked-list.o
	$(CCLINK) -shared linked-list.o -o liblinked-list.so
libgrades.so: grades.o
	$(CCLINK) -shared grades.o -o libgrades.so
linked-list.o: linked-list.c linked-list.h
	$(CC) -c -fpic linked-list.c
grades.o: grades.c grades.h
	$(CC) -c -fpic grades.c

#clean objects
clean:
	$(RM)

