SRCS := $(wildcard *.cc)
EXES := $(basename $(SRCS))
CXXFLAGS := -Wall -g 
all: $(EXES)
%: %.cc
	$(CXX) $(CXXFLAGS) $< -o $@
clean: 
	$(RM) $(EXES)
.PHONY: all clean
