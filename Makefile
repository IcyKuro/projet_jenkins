# Makefile - tri a bulles (Linux, WSL, MSYS2/MinGW)
ifeq ($(OS),Windows_NT)
  EXE = .exe
endif

CC      = gcc
CFLAGS  = -Wall -Wextra -g -O0
PREFIX ?= /usr/local
TARGET  = tri_bulles$(EXE)
TEST    = tests/test_tri$(EXE)

all: $(TARGET)

$(TARGET): tri_bulles.c
	$(CC) $(CFLAGS) -o $@ $<

$(TEST): tests/test_tri.c tri_bulles.c
	$(CC) $(CFLAGS) -o $@ tests/test_tri.c

test: $(TEST)
	./$(TEST)

install: $(TARGET)
	mkdir -p $(PREFIX)/bin
	cp $(TARGET) $(PREFIX)/bin/

clean:
	rm -f tri_bulles tri_bulles.exe tests/test_tri tests/test_tri.exe

.PHONY: all test install clean
