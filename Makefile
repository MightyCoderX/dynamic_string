CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c23 -g

SRCS := main.c dynamic_string/dynamic_string.c

main: $(SRCS)
	${CC} ${CFLAGS} $(SRCS) -o $@

run: main
	./main

debug: main
	gdb ./main

clean: main
	rm main

