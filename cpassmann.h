#include <stdio.h>
#include <stdlib.h>
#include "initialize.h"
void testinitialize() {
  char **arr = initialize();
  for (int i = 0 ; i < 2 ;i++){
    printf("%s\n",arr[i]);

  }}
