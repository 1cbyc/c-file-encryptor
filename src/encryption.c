#include <stdio.h>
#include <string.h>
#include "encryption.h"

void encrypt_file(const char *input_file, const char *output_file, const char *key) {
    FILE *in_file = fopen(input_file, "rb");
    FILE *out_file = fopen(output_file, "wb");
    if (!in_file || !out_file) {
        perror("File opening failed");
        return;
    }

    size_t key_len = strlen(key);
    int byte;
    size_t i = 0;

    while ((byte = fgetc(in_file)) != EOF) {
        fputc(byte ^ key[i % key_len], out_file);
        i++;
    }

    fclose(in_file);
    fclose(out_file);
}

void decrypt_file(const char *input_file, const char *output_file, const char *key) {
    // Decryption logic is the same as encryption with XOR
    encrypt_file(input_file, output_file, key);
}
