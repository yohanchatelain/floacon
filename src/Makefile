DEBUG = -Wall -g
LDLIBS = -lmpfr -lgmp
BIN = floacon
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

default: $(BIN)
all: default

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@ ${LDLIBS}

$(BIN): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ ${LDLIBS}

clean:
	rm -f *.o
	rm -f $(BIN)