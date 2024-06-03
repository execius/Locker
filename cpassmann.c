#include <stdio.h>
#include <stdlib.h>
#include "initialize.h"
void main(){
  char **arr = malloc(NUMBEROFINF*sizeof(int));
  arr[0] = malloc(MAXLENGH*sizeof(int));
  arr[1] = malloc(MAXLENGH*sizeof(int));
  arr = initialize();
  for (int i = 0 ; i < 2 ;i++){
    printf("%s\n",arr[i]);

  }}
