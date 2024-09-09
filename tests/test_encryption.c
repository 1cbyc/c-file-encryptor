#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "encryption.h"

void test_encryption_decryption() {
    const char *test_input = "test_input.txt";
    const char *encrypted_output = "encrypted_output.txt";
    const char *decrypted_output = "decrypted_output.txt";
    const char *key = "secret";

    FILE *fp = fopen(test_input, "w");
    assert(fp != NULL);
    fprintf(fp, "this is the test.");
    fclose(fp);

    encrypt_file(test_input, encrypted_output, key);

    decrypt_file(encrypted_output, decrypted_output, key);

    FILE *in_fp = fopen(test_input, "r");
    FILE *out_fp = fopen(decrypted_output, "r");

    assert(in_fp != NULL);
    assert(out_fp != NULL);

    char in_char, out_char;
    int match = 1;

    while ((in_char = fgetc(in_fp)) != EOF && (out_char = fgetc(out_fp)) != EOF) {
        if (in_char != out_char) {
            match = 0;
            break;
        }
    }

    if (fgetc(in_fp) != EOF || fgetc(out_fp) != EOF) {
        match = 0;
    }

    fclose(in_fp);
    fclose(out_fp);

    assert(match && "Decryption did not match the original input!");
    printf("Test passed: Encryption and decryption work correctly!\n");
}

int main() {
    test_encryption_decryption();
    return 0;
}
