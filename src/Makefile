DEBUG_FLAGS = -Wall -g -DDEBUG
CFLAGS = -fPIC
LDLIBS = -lmpfr -lgmp
BIN = floacon
LIB = libfloacon.so
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

# If the environment variable ENABLE_DEBUG is set to 1, add -DDEBUG to CFLAGS
ifeq ($(DEBUG), 1)
	CFLAGS += $(DEBUG_FLAGS)
endif

default: $(BIN)
all: default

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@ ${LDLIBS}

$(LIB): $(OBJECTS)
	@echo "Building $(LIB)..."
	$(CC) $(OBJECTS) -shared -o $@ ${LDLIBS}

$(BIN): $(LIB)
	@echo "Building $(BIN)..."
	$(CC) $(OBJECTS) -o $@ ${LDLIBS} -Lsrc/ -lfloacon

clean:
	rm -f *.o
	rm -f $(BIN)