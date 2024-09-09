#include <studio.h>
#include <stdlib.h>
#include <string.h>
#include "encryption.h"

void print_usage() {
    printf("Usage: ./c-file-encryptor <encrypt|decrypt> <input_file> <output_file> <key>\n");
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        print_usage
    }
}