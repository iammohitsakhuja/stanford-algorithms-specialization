# Makefile

# Compiler to use
CC ?= cc

# Flags to pass to compiler
CFLAGS ?= -fsanitize=signed-integer-overflow -fsanitize=undefined -ggdb3 -O0 \
		  -Qunused-arguments -std=c11 -Wall -Werror -Wextra -Wno-sign-compare \
		  -Wno-unused-parameter

# Name for executable
EXE = 2sum

# Space separated list of header-files
HDRS = hash_table.h benchmark.h helpers.h

# Space separated list of libraries, if any,
# each of which should be prefixed with -l
LIBS =

# Space separated list of source-files
SRCS = main.c hash_table.c benchmark.c helpers.c

# Automatically generated list of object files
OBJS = $(SRCS:.c=.o)

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

