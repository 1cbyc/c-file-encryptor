#ifndef ENCRYPTOR_H
#define ENCRYPTOR_H

#include <stdio.h>
#include <openssl/aes.h>
#include <openssl/sha.h>
#include <openssl/rand.h>

void encrypt_file(const char *input_file, const char *output_file, const unsigned char *key);
void decrypt_file(const char *input_file, const char *output_file, const unsigned char *key);
void generate_key_from_password(const char *password, unsigned char *key);
void sha256_hash_file(const char *filename, unsigned char *hash);
int verify_integrity(const char *input_file, const unsigned char *original_hash);
void log_action(const char *message);
void handle_error(const char *error_message);

#endif
