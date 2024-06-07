#include <stdlib.h>
#include <stdio.h>
#ifndef EROR_HANDLING_H

#define EROR_HANDLING_H



void log_error(const char *message);

enum ErrorCode {
  SUCCESS = 0,
  ERROR_INDEX_OUT_OF_BOUNDS = -1,
  ERROR_MEMORY_ALLOCATION = -2,
  ERROR_INVALID_STRING = -3,
  ERROR_INVALID_INTEGER = -4,
  ERROR_UNKNOWN_TYPE = -5
};

#endif 
