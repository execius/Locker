#include <stdio.h>
#include <stdlib.h>
#define NUMBEROFINFO 4

#define USERINDEX 0
#define EMAILINDEX 1
#define PASSWORDINDEX 2 
#define PLATFORMINDEX 3

#define MAXLEN 4096
#define MAXNUMBER 9999


struct account { 
  char *array[MAXLEN];
  int accountnumber;
} ;
int changemember(struct account* acc,int index ,char *newval,char *type);
