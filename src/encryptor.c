#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include "encryptor.h"
#include "sha256.h"

#define AES_KEY_SIZE 32
#define BLOCK_SIZE 16

void encrypt_file(const char *input_file, const char *output_file, const unsigned char *key) {
    FILE *fin = fopen(input_file, "rb");
    FILE *fout = fopen(output_file, "wb");

    if (!fin || !fout) {
        handle_error("Error opening file");
        return;
    }

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        handle_error("Error creating cipher context");
        fclose(fin);
        fclose(fout);
        return;
    }

    unsigned char iv[BLOCK_SIZE];
    if (!RAND_bytes(iv, sizeof(iv))) {
        handle_error("Error generating IV");
        fclose(fin);
        fclose(fout);
        EVP_CIPHER_CTX_free(ctx);
        return;
    }

    fwrite(iv, 1, BLOCK_SIZE, fout); // save the iv

    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) {
        handle_error("Error initializing encryption");
        fclose(fin);
        fclose(fout);
        EVP_CIPHER_CTX_free(ctx);
        return;
    }

    unsigned char inbuf[BLOCK_SIZE];
    unsigned char outbuf[BLOCK_SIZE + EVP_MAX_BLOCK_LENGTH];
    int outlen, bytes_read;

    


    AES_KEY aes_key;
    AES_set_encrypt_key(key, 256, &aes_key);

    unsigned char inbuf[BLOCK_SIZE];
    unsigned char outbuf[BLOCK_SIZE];
    unsigned char iv[BLOCK_SIZE];

    if (!RAND_bytes(iv, sizeof(iv))) {
        handle_error("Error generating IV");
        fclose(fin);
        fclose(fout);
        return;
    }

    fwrite(iv, 1, BLOCK_SIZE, fout); // save the iv

    int bytes_read;
    while ((bytes_read = fread(inbuf, 1, BLOCK_SIZE, fin)) > 0) {
        AES_encrypt(inbuf, outbuf, &aes_key);
        fwrite(outbuf, 1, BLOCK_SIZE, fout);
    }

    fclose(fin);
    fclose(fout);
    log_action("File encrypted successfully.");
}

void decrypt_file(const char *input_file, const char *output_file, const unsigned char *key) {
    FILE *fin = fopen(input_file, "rb");
    FILE *fout = fopen(output_file, "wb");

    if (!fin || !fout) {
        handle_error("Error opening file");
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
    }

    fclose(fin);
    fclose(fout);
    log_action("File decrypted successfully.");
}

void log_action(const char *message) {
    FILE *log_file = fopen("../logs/encryptor.log", "a");
    if (log_file) {
        fprintf(log_file, "%s\n", message);
        fclose(log_file);
    }
}
