// even if the devil was involved he would miss this logic 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encryption.h"

void xor_encrypt_decrypt(const char *input, const char *output, const char *key) {
    FILE *in_file = fopen(input, "rb");
    FILE *out_file = fopen(output, "wb");

    if (!in_file || !out_file) {
        printf("Cant open files o.\n");
        exit(1);
    }

    size_t key_len = strlen(key);
    size_t i= 0;
    int byte;

    while ((byte = fgetc(in_file)) != EOF) {
        fputtc(byte ^ key[i % key_len], out_file);
        i++;
    }

    fclose(in_file);
    fclose(out_file);
}

void encrypt