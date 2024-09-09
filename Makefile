# CC = gcc
# CFLAGS = -Wall -Wextra -Iinclude
# SRC = src/main.c src/encryption.c
# EXEC = c-file-encryptor

# all: $(EXEC)

# $(EXEC): $(SRC)
# 	$(CC) $(CFLAGS) $(SRC) -o $(EXEC)

# clean:
# 	rm -f $(EXEC)

# .PHONY: all clean
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRC = src/main.c src/encryption.c
EXEC = c-file-encryptor
TEST_SRC = tests/test_encryption.c
TEST_EXEC = test_encryption

all: $(EXEC)

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC)

test: $(TEST_SRC)
	$(CC) $(CFLAGS) $(TEST_SRC) src/encryption.c -o $(TEST_EXEC)
	./$(TEST_EXEC)

clean:
	rm -f $(EXEC) $(TEST_EXEC)

.PHONY: all test clean
