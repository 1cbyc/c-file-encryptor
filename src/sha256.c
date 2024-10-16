#include <stdio.h>
#include <openssl/sha.h>
#include "sha256.h"

void sha256_hash_file(const char *filename, unsigned char *hash) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        return;
    }

    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (mdctx == NULL) {
        perror("Error creating digest context");
        fclose(file);
        return;
    }

    if (1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL)) {
        perror("Error initializing digest");
        EVP_MD_CTX_free(mdctx);
        fclose(file);
        return;
    }

    // SHA256_CTX sha256;
    // SHA256_Init(&sha256);

    unsigned char buffer[1024];
    int bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        if (1 != EVP_DigestUpdate(mdctx, buffer, bytes_read)) {
            perror("Error updating digest");
            EVP_MD_CTX_free(mdctx);
            fclose(file);
            return;
        }
        // SHA256_Update(&sha256, buffer, bytes_read);
    }

    unsigned int hash_len;
    if (1 != EVP_DigestFinal_ex(mdctx, hash, &hash_len)) {
        perror("Error finalizing digest");
    }

    EVP_MD_CTX_free(mdctx);
    fclose(file);
    // SHA256_Final(hash, &sha256);
    // fclose(file);
}
