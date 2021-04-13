src = $(wildcard *.c)
target = $(patsubst %.c, %, $(src))

CC = gcc
CFLAGS = -Wall -g

ALL:$(target)

$(target):%:%.c
	$(CC) $< -o $@ $(CFLAGS)

$(obj):%.o:%.c
	$(CC) -c -Wall $< -o $@

.PHONY:clean

clean:
	rm -rf $(target) 
