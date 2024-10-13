CC = gcc
CFLAGS = -Wall -lssl -lcrypto

all: encryptor

encryptor: src/encryptor.c src/sha256.c src/utils.c
	$(CC) $(CFLAGS) -o encryptor src/encryptor.c src/sha256.c src/utils.c

encryptor: src/encryptor.c src/sha256.c src/utils.c


clean:
	rm -f encryptor
