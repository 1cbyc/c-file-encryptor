#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/sha.h>
#include <openssl/rand.h>
#include "encryptor.h"

#define AES_KEY_SIZE 32 // 256-bit key
#define BLOCK_SIZE 16

// progress feedback function
void progress_feedback(long processed, long total) {
    float percentage = ((float)processed / total) * 100;
    printf("\rProgress: %.2f%%", percentage);
    fflush(stdout);
}

// generate key from password using sha-256
void generate_key_from_password(const char *password, unsigned char *key) {
    SHA256((const unsigned char *)password, strlen(password), key);
}

// encrypt the file
void encrypt_file(const char *input_file, const char *output_file, const unsigned char *key) {
    FILE *fin = fopen(input_file, "rb");
    FILE *fout = fopen(output_file, "wb");

    if (!fin || !fout) {
        perror("Error opening files");
        return;
    }

    AES_KEY aes_key;
    AES_set_encrypt_key(key, 256, &aes_key);

    unsigned char inbuf[BLOCK_SIZE];
    unsigned char outbuf[BLOCK_SIZE];
    unsigned char iv[BLOCK_SIZE];

    if (!RAND_bytes(iv, sizeof(iv))) {
        perror("Error generating IV");
        fclose(fin);
        fclose(fout);
        return;
    }

    fwrite(iv, 1, BLOCK_SIZE, fout); // save the iv for decryption

    int bytes_read;
    while ((bytes_read = fread(inbuf, 1, BLOCK_SIZE, fin)) > 0) {
        AES_encrypt(inbuf, outbuf, &aes_key);
        fwrite(outbuf, 1, BLOCK_SIZE, fout);
        progress_feedback(ftell(fin), 0);  // feedback progress
    }

    fclose(fin);
    fclose(fout);
    printf("\nEncryption complete.\n");
}

// decrypt the file
void decrypt_file(const char *input_file, const char *output_file, const unsigned char *key) {
    FILE *fin = fopen(input_file, "rb");
    FILE *fout = fopen(output_file, "wb");

    if (!fin || !fout) {
        perror("Error opening files");
        return;
    }

    AES_KEY aes_key;
    AES_set_decrypt_key(key, 256, &aes_key);

    unsigned char inbuf[BLOCK_SIZE];
    unsigned char outbuf[BLOCK_SIZE];
    unsigned char iv[BLOCK_SIZE];

    fread(iv, 1, BLOCK_SIZE, fin); // read the iv

    int bytes_read;
    while ((bytes_read = fread(inbuf, 1, BLOCK_SIZE, fin)) > 0) {
        AES_decrypt(inbuf, outbuf, &aes_key);
        fwrite(outbuf, 1, BLOCK_SIZE, fout);
        progress_feedback(ftell(fin), 0);  // feedback progress
    }

    fclose(fin);
    fclose(fout);
    printf("\nDecryption complete.\n");
}

// calculate sha-256 hash of a file
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

// verify file integrity
int verify_integrity(const char *input_file, const unsigned char *original_hash) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    sha256_hash_file(input_file, hash);
    return memcmp(original_hash, hash, SHA256_DIGEST_LENGTH) == 0;
}

int main(int argc, char *argv[]) {
    if (argc < 5) {
        printf("Usage: %s <encrypt/decrypt> <input_file> <output_file> <password>\n", argv[0]);
        return 1;
    }

    const char *mode = argv[1];
    const char *input_file = argv[2];
    const char *output_file = argv[3];
    const char *password = argv[4];

    unsigned char key[AES_KEY_SIZE];
    generate_key_from_password(password, key);

    if (strcmp(mode, "encrypt") == 0) {
        encrypt_file(input_file, output_file, key);

        unsigned char hash[SHA256_DIGEST_LENGTH];
        sha256_hash_file(input_file, hash);
        printf("File hash (sha-256) for verification: ");
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            printf("%02x", hash[i]);
        }
        printf("\n");

    } else if (strcmp(mode, "decrypt") == 0) {
        decrypt_file(input_file, output_file, key);
    } else {
        printf("Invalid mode. Use 'encrypt' or 'decrypt'.\n");
    }

    return 0;
}
