all: clean build

clean:
	@if [ -f mem_alloc ]; then rm mem_alloc; fi
build:
	gcc -o mem_alloc -Wall -Wpedantic -Werror mem_alloc.c
