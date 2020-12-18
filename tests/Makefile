.POSIX:

CC = gcc

CCFLAGS = -DEBUG -g -c

REQ = ../util
COMPATH = ../components/
COM = coutil battery ip date memory volume keymap cpu

RCOM = $(addprefix $(COMPATH), $(COM) )

all: test
	@echo "ddd"

print:
	@echo $(RCOM)

test: test.o $(COM:=.o)
	@echo TBEGIN
	$(CC) $(COM:=.o) test.o -lX11 -o $@
	@echo TEND
	
%.o: test.c test.h ../components.h $(RCOM:=.c) 
	@echo OBEGIN
	$(CC) $(CCFLAGS) test.c $(RCOM:=.c)
	@echo OEND

clean:
	rm -f test *.o 

.PHONY: clean print
