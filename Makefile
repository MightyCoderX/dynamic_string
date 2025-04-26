CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic

SRCS := main.c dynamic_string/dynamic_string.c
EXE_NAME := main

main: $(SRCS)
	${CC} ${CFLAGS} $(SRCS) -o $(EXE_NAME)

run: main
	./main

debug: $(SRCS)
	${CC} ${CFLAGS} -g -fsanitize=address $(SRCS) -o $(EXE_NAME)
	gdb ./main

clean: main
	rm main

