.DEFAULT_GOAL := all
.PHONY: clean

ranges: ranges.c
	gcc -o ranges ranges.c

all: ranges

test: ranges
	./ranges

install: ranges
	cp ranges /usr/bin/

clean:
	rm -f ranges
