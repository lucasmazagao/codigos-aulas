CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -Wpedantic
LDFLAGS :=
LDLIBS :=
TARGET := main
OBJS := main.o LinkedList.o BigInt.o

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS)

%.o: %.c LinkedList.h BigInt.h
	$(CC) $(CFLAGS) -c $<

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)