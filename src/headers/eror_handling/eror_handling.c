#include "eror_handling.h"

//logs erors to stderr
void log_error(const char *message) {
    fprintf(stderr, "%s\n", message);
}



