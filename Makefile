CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRC = src/main.c src/encryption.c
EXEC = c-file-encryptor

all: $(EXEC)

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC)

clean:
	rm -f $(EXEC)

.PHONY: all clean
