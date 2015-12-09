all: sier may

CC = gcc
CFLAGS= -Wall -Wformat -lX11 -lm
SOURCES = $(wildcard lib/*/*.c)
INCLUDE = lib

build: $(DEPS)
	@mkdir -p build

sier: build
	$(CC) -s $(SOURCES) $(CFLAGS) -I$(INCLUDE) -o build/sier src/sier.c

may: build
	$(CC) -s $(SOURCES) $(CFLAGS) -I$(INCLUDE) -o build/may src/may.c

clean:
	@rm -f build/*
	@rm -d build
