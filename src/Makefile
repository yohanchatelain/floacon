DEBUG_FLAGS = -Wall -g -DDEBUG
LDLIBS = -lmpfr -lgmp
BIN = floacon
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

# If the environment variable ENABLE_DEBUG is set to 1, add -DDEBUG to CFLAGS
ifeq ($(DEBUG), 1)
	CFLAGS += $(DEBUG_FLAGS)
endif

default: $(BIN)
all: default

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@ ${LDLIBS}

$(BIN): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ ${LDLIBS}

clean:
	rm -f *.o
	rm -f $(BIN)