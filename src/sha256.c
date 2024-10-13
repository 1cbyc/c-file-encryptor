#include <stdio.h>
#include <openssl/sha.h>
#include "sha256.h"

void sha256_hash_file(const char *filename, unsigned char *hash) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        return;
    }

    SHA256_CTX sha256;
    SHA256_Init(&sha256);

    unsigned char buffer[1024];
    int bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        SHA256_Update(&sha256, buffer, bytes_read);
    }

    SHA256_Final(hash, &sha256);
    fclose(file);
}
