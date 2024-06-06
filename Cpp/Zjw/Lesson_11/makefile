SOUS:=$(wildcard *.cc)
OUTS:= $(patsubst %.cc,%,$(SOUS))
OBJS:= $(patsubst %.cc,%.o,$(SOUS))
o:$(OBJS)
CXX:=g++
%.o:%.cc
	$(CXX) -c $^ -o $@
all:$(OUTS)
%:%.o
	$(CXX) $^ -o $@

#00_lambda:00_lambda.o
#	$(CXX) $^ -o $@
#00_lambda.o:00_lambda.cc
#	$(CXX) -c $^ -o $@
#01_sequence:01_sequence.o
#	$(CXX) $^ -o $@
#01_sequence.o:01_sequence.cc
#	$(CXX) -c $^ -o $@
#02_auto_ptr:02_auto_ptr.o
#	$(CXX) $^ -o $@
#02_auto_ptr.o:02_auto_ptr.cc
#	$(CXX) -c $^ -o $@
#03_type_cast:03_type_cast.o
#	$(CXX) $^ -o $@
#03_type_cast.o:03_type_cast.cc
#	$(CXX) -c $^ -o $@

clean:
	rm -rf $(OBJS) $(OUTS)
