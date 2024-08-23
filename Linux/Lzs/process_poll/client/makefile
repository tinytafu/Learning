SRCS:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,$(SRCS))
CC:= gcc
client:$(OBJS)
%:%.o
	$(CC)  $^ -o $@ -g
%.o:%.c
	$(CC) -c $^ -o $@
clean:
	$(RM) $(OBJS) client
rebuild:clean client
