CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: cacher

cacher: cacher.o linkedList.o myFuncs.o
	$(CC) $(CFLAGS) -o cacher cacher.c linkedList.c myFuncs.c

%.o: %.c
	$(CC) $(CFLAGS) $< -c

clean:
	rm -f cacher *.o *.bin

format:
	clang-format -i -style=file *.[ch]
