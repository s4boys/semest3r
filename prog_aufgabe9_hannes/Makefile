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
	ifeq "$(findstring Windows,$(OS))" "Windows"

	else
	rm *.o main
clear:
	rm *.o main
cl:
	rm *.o main

test: all
