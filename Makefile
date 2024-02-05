CC = gcc
CFLAGS = -Wall -I./include -I./common

SRCDIR = src
COMMONDIR = common
EXDIR = example
BINDIR = bin

# Source files
SRC = $(wildcard $(SRCDIR)/*.c) $(wildcard $(EXDIR)/*.c)
OBJ = $(SRC:.c=.o)

# Executable
EXEC = example_exec

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(BINDIR)/$@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJ) $(BINDIR)/$(EXEC)
