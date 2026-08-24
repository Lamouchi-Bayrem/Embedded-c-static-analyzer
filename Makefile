CC=gcc
CFLAGS=-Wall -Wextra -g -fPIC -Iinclude
EXEC=main
LIBNAME=libtechleef
SOLIB=$(LIBNAME).so
SONAME=$(SOLIB).1
LIB=$(SONAME).0

$(EXEC): src/main.o $(SOLIB)
	$(CC) src/main.o -L. -ltechleef -o $@

$(SOLIB): src/techleef.o
	$(CC) $< -shared -Wl,-soname=$(SONAME) -o $(LIB)
	ln -sf $(LIB) $(SONAME)
	ln -sf $(SONAME) $(SOLIB)

%.o: %.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@

clean:
	rm -f src/*.o src/*.d $(EXEC) *.so*

run:
	LD_LIBRARY_PATH=. ./$(EXEC)
