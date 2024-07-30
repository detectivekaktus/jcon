BUILD_DIR = build

CC = gcc
CFLAGS = -Wall -Wextra -pedantic -ggdb -std=c99 -fsanitize=undefined

all: $(BUILD_DIR)
	$(CC) $(CFLAGS) -fpic -c src/jcon.c -o $(BUILD_DIR)/jcon.o
	$(CC) $(CFLAGS) -shared $(BUILD_DIR)/jcon.o -o $(BUILD_DIR)/libjcon.so

static: $(BUILD_DIR)
	$(CC) $(CFLAGS) -c src/jcon.c -o $(BUILD_DIR)/jcon.o
	ar rcs $(BUILD_DIR)/libjcon.a $(BUILD_DIR)/jcon.o

test: $(BUILD_DIR)
	$(CC) $(CFLAGS) -c src/jcon.c -o $(BUILD_DIR)/jcon.o
	$(CC) $(CFLAGS) -c test.c -o $(BUILD_DIR)/test.o
	$(CC) $(CFLAGS) -o test $(BUILD_DIR)/jcon.o $(BUILD_DIR)/test.o

$(BUILD_DIR):
	mkdir $@

$(BUILD_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -r $(BUILD_DIR)

.PHONY: all clean
