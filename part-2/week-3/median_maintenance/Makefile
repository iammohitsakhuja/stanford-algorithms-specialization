# Makefile

# Compiler to use
CXX ?= c++

# Flags to pass to compiler
CXXFLAGS ?= -fsanitize=signed-integer-overflow -fsanitize=undefined -ggdb3 \
			-O0 -Qunused-arguments -std=c++17 -Wall -Werror -Wextra \
			-Wno-sign-compare -Wno-unused-parameter

# Name for executable
EXE = median

# Space separated list of header-files
HDRS = DualHeap.hh Tree.hh TreeNode.hh benchmark.hh

# Space separated list of libraries, if any,
# each of which should be prefixed with -l
LIBS =

# Space separated list of source-files
SRCS = main.cc DualHeap.cc Tree.cc TreeNode.cc benchmark.cc

# Automatically generated list of object files
OBJS = $(SRCS:.cc=.o)

.PHONY: all
all: $(EXE)

# Default target
$(EXE): $(OBJS) $(HDRS) Makefile
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LIBS)

# Dependencies
$(OBJS): $(HDRS) Makefile

.PHONY: clean
clean:
	rm -f core $(EXE) *.o

