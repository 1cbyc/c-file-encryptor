#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encryption.h"

// void print_usage() {
//     printf("Usage: ./c-file-encryptor <encrypt|decrypt> <input_file> <output_file> <key>\n");
// }
void print_usage() {
    printf("Usage:\n");
    printf("  encrypt <input_file> <output_file> <key>\n");
    printf("  decrypt <input_file> <output_file> <key>\n");
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        print_usage();
        return EXIT_FAILURE;
        // return 1;
    }

    const char *action = argv[1];
    const char *input_file = argv[2];
    const char *output_file = argv[3];
    const char *key = "secret";  // will be the default key

    // char *mode = argv[1];
    // char *input_file = argv[2];
    // char *output_file = argv[3];
    // char *key = argv[4];

    if (strcmp(action, "encrypt") == 0) {
        encrypt_file(input_file, output_file, key);
    } else if (strcmp(action, "decrypt") == 0) {
        decrypt_file(input_file, output_file, key);
    } else {
        print_usage();
        return EXIT_FAILURE;
    }

    // if (strcmp(mode, "encrypt") == 0) {
    //     encrypt_file(input_file, output_file, key);
    // } else if (strcmp(mode, "decrypt") == 0) {
    //     decrypt_file(input_file, output_file, key);
    // } else {
    //     print_usage();
    //     return 1;
    // }

    printf("%s operation completed haha!\n", mode);
    return 0;
}