# -*- Makefile -*-

all:
	make -f Makefile.shared install
	make -f Makefile.main

clean:
	make -f Makefile.main clean
	make -f Makefile.shared clean

clear:
	clean

cl:
	clean

test: all
	./main

install: