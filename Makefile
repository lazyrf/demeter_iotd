TARGET := demeter_iotd

CC := gcc
AS := as
AR := ar
LD := ld

CFLAGS := -I.

OBJS := $(patsubst %.c, %.o, $(wildcard *.c))

all: $(OBJS)
	$(CC) -o $(TARGET) $^

%.o: %.c
	$(CC) -c -o $@ $^ $(CFLAGS)

clean:
	rm -rf *.o
