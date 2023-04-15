.PHONY: clean main

CFLAGS=-g3

main: main.elf
	./$<

main.elf: main.c
	gcc -o $@ $^ ${CFLAGS}

bench: main.elf
	hyperfine --show-output ./$<

clean:
	rm main.elf
