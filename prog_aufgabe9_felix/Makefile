all:
ifeq (${CONF},LINUX)
	make -f Makefile.foo
	make -f Makefile.shared
	make -f Makefile.main
	@echo "CONF ist "${CONF}
else
 ifeq (${CONF},WINDOWS)
	make -f Makefile.foo
	make -f Makefile.shared
	make -f Makefile.main
	@echo "CONF ist "${CONF}
 else 
	$(error Konfigurationsfehler)
 endif
endif


clean:
	rm *.o main.exe *.dll *.so
clear:
	rm *.o main.exe *.dll *.so
cl:
	rm *.o main.exe *.dll *.so

test: all
