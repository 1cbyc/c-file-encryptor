// even if the devil was involved he would miss this logic 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encryption.h"

void xor_encrypt_decrypt(const char *input, const char *output, const char *key) {
    FILE *in_file = fopen(input, "rb");
    FILE *out_file = fopen(output, "wb")
}