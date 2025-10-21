# Makefile para compilar main.c e Stack.c
CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -Wpedantic
LDFLAGS :=
LDLIBS :=
TARGET := main
OBJS := main.o Stack.o

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS)

# Regras de compilação (main.c e Stack.c dependem de Stack.h)
%.o: %.c Stack.h
	$(CC) $(CFLAGS) -c $<

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
