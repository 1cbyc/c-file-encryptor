#include <studio.h>
#include <stdlib.h>
#include <string.h>
#include "encryption.h"

void print_usage() {
    printf("Usage: ./c-file-encryptor <encrypt|decrypt> <input_file> <output_file> <key>\n");
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        print_usage();
        return 1;
    }

    char *mode = argv[1];
    char *input_file = argv[2];
    char *output_file = argv[3];
    char *key = argv[4];

    if (strcmp(mode, "encrypt"))
}