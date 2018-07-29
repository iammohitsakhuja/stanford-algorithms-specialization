# Makefile

# Compiler to use
CXX ?= c++

# Flags to pass to compiler
CXXFLAGS ?= -fsanitize=signed-integer-overflow -fsanitize=undefined -ggdb3 -O0 -Qunused-arguments -std=c++17 -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter

# Name for executable
EXE = randomized_selection

# Space separated list of header-files
HDRS = rselect.hpp helpers.hpp benchmark.hpp quicksort.hpp

# Space separated list of libraries, if any,
# each of which should be prefixed with -l
LIBS =

# Space separated list of source-files
SRCS = main.cpp rselect.cpp helpers.cpp benchmark.cpp quicksort.cpp

# Automatically generated list of object files
OBJS = $(SRCS:.cpp=.o)

.PHONY: all
all: $(EXE)

# Default target
$(EXE): $(OBJS) $(HDRS) Makefile
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

# Dependencies
$(OBJS): $(HDRS) Makefile

.PHONY: clean
clean:
	rm -f core $(EXE) *.o

