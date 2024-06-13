#include "utilities.h"

int * intdup(int const * src, size_t len)
{
   int * p = malloc(len * sizeof(int));
   if(NULL == p){
     log_error("error: memory allocation failed, function: intdup");
      return NULL;
  }
    
   memcpy(p, src, len * sizeof(int));
   return p;
}
