all:=target
SRUS:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,$(SRUS))
CC:=gcc
$(all):$(OBJS)
	$(CC) $^ -o $@
%.o:%.c
	$(CC) -c $^ -o $@
#main:main.o add.o
#	gcc main.o add.o -o main
#main.o:main.c
#	gcc -c main.c -o main.o
#add.o:add.c
#gcc -c add.c -o add.o
.PHONY:clean rebuild
clean:
	rm -rf $(OBJS) $(all)
rebuild:clean target
