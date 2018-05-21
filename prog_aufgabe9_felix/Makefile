all:
ifeq (${CONF},LINUX)
	export LD_LIBRARY_PATH=.
	make -f Makefile.foo
	make -f Makefile.shared CONF=LINUX
	make -f Makefile.main CONF=LINUX
	@echo "CONF ist "${CONF}
else
 ifeq (${CONF},WINDOWS)
	make -f Makefile.foo
	make -f Makefile.shared CONF=WINDOWS
	make -f Makefile.main CONF=WINDOWS
	@echo "CONF ist "${CONF}
 else 
	$(error Konfigurationsfehler. Bitte CONF=WINDOWS oder CONF=LINUX angeben.)
 endif
endif


clean:
	rm -f *.o main main.exe *.dll *.so
clear:
	rm -f *.o main main.exe *.dll *.so
cl:
	rm -f *.o main main.exe *.dll *.so

test: all
