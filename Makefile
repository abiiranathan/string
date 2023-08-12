SANITIZERS=-fsanitize=address -fsanitize=bounds -fsanitize=undefined
CFLAGS=-Wall -Werror -pedantic -ggdb
CC=/usr/bin/gcc
SRCS=string_test.c string.c

test:
	${CC} ${CFLAGS} ${SANITIZERS} ${SRCS}

docs:
	doxygen Doxyfile