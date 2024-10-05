SRCS = $(wildcard *.cc)
EXES = $(basename $(SRCS))
CXXFLAGS := -Wall -g
all: $(EXES)
%: %.cc
	$(CXX) $(CXXFLAGS) $< -o $@
.PHONY: clean all
clean: 
	$(RM) $(EXES)
