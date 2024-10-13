#include <stdio.h>
#include <stdlib.h>
#include "encryptor.h"

void handle_error(const char *error_message) {
    fprintf(stderr, "%s\n", error_message);
    log_action(error_message);
    exit(1);
}
