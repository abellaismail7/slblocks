.POSIX:

PREFIX = /usr/local
CC = gcc


CCFLAGS = -c

debug: CCFLAGS += -g

debug: slblocks

all: slblocks

COMPATH = components/
COM = coutil battery ip date memory shell keymap loading wifi cpu disk kernel_release hostname

RCOM = $(addprefix $(COMPATH), $(COM) ) 

print:
	@echo $(CCFLAGS)


slblocks: slblocks.o $(COM:=.o)
	$(CC) slblocks.o $(COM:=.o) -lX11 -o slblocks

slblocks.o: slblocks.c config.h components.h $(RCOM:=.c)
	$(CC) $(CCFLAGS) slblocks.c $(RCOM:=.c)

clean:
	rm -f *.o *.gch slblocks

install: slblocks
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f slblocks $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/slblocks
uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/slblocks

.PHONY: clean debug install uninstall
