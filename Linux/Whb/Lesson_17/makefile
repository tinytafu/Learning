.PHONY:all
all:myexec mycmd
myexec:myexec.c
	gcc $? -o $@
mycmd:mycmd.cc
	g++ $? -o $@
.PHONY:clean
clean:
	rm -rf mycmd myexec
