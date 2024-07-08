SRCS:=$(wildcard *.cc)
EXES:=$(patsubst %.cc,%,$(SRCS))
CC:= g++
all:$(EXES)
%:%.c
	$(CC) $^ -Wall -std=c++11 -o $@ -g
clean:
	$(RM) $(EXES)
rebuild:clean all
