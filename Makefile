CC = gcc
CFLAGS = -Wall -lssl -lcrypto

all: encryptor

encryptor: src/encryptor.c src/sha256.c src/utils.c
	$(CC) $(CFLAGS) -o encryptor src/encryptor.c src/sha256.c src/utils.c

encryptor: src/encryptor.c src/sha256.c src/utils.c
    gcc -Wall -o encryptor src/encryptor.c src/sha256.c src/utils.c -lssl -lcrypto


clean:
	rm -f encryptor
