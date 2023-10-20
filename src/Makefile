CC = gcc
CFLAGS = -Wall -Wextra -Werror
BUILD = ../build
NAME = graph

all: graph.c
	$(CC) $(CFLAGS) list.c rpn.c print.c graph.c -o $(BUILD)/$(NAME)
	clang-format -i *.c *.h

clean:
	rm -rf $(BUILD)/$(NAME)


