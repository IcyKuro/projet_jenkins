# Makefile - tri a bulles (Linux / Docker, et MSYS2 pour tester sous Windows)
ifeq ($(OS),Windows_NT)
  EXE = .exe
endif

CC      = gcc
WARN    = -Wall -Wextra -Werror
CFLAGS ?= -O2
PREFIX ?= /usr/local
TARGET  = tri_bulles$(EXE)
TEST    = tests/test_tri_bulles$(EXE)

all: $(TARGET)

$(TARGET): main.o tri_bulles.o
	$(CC) $(WARN) $(CFLAGS) -o $@ $^

%.o: %.c tri_bulles.h
	$(CC) $(WARN) $(CFLAGS) -c $<

# Version de pre-prod : symboles de debug et sans optimisation pour valgrind
debug:
	$(MAKE) distclean
	$(MAKE) CFLAGS="-g -O0"

$(TEST): tests/test_tri_bulles.c tri_bulles.o
	$(CC) $(WARN) $(CFLAGS) -o $@ $^

test: $(TEST)
	./$(TEST)

# clean garde l'executable, sinon la sequence compilation, clean, strip du sujet est impossible
clean:
	rm -f *.o $(TEST)

distclean: clean
	rm -f $(TARGET)

# Pas de dependance sur $(TARGET) : make recompilerait apres le clean et annulerait le strip
strip:
	strip --strip-all $(TARGET)

install:
	mkdir -p $(PREFIX)/bin
	cp $(TARGET) $(PREFIX)/bin/

.PHONY: all debug test clean distclean strip install
