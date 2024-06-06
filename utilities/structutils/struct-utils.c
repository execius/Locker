#include "struct-utils.h"
#include <string.h>
#include <ctype.h>

struct account changemember(struct account acc,int index ,char *newval,char *type){
  if (strcmp(type,"char")== 0){
    if(index <= NUMBEROFINFO && strlen(newval) <= MAXLEN && *newval)
      (acc.array)[index] = newval;
    else {
      perror("eror : newval too long or index out of bounds , function : changemember ");
      exit(EXIT_FAILURE);
    }  
  }
  else if (strcmp(type,"int")== 0){
    if (isdigit(*newval) && *newval && atoi(newval) <= MAXNUMBER)
      acc.accountnumber = atoi(newval);
    else {
      perror("eror : newval not int or above maximum , function : changemember");
      exit(EXIT_FAILURE);
    }

  }
  else {
    perror("bad type indicator given, function : changemember ");
    exit(EXIT_FAILURE);
  }
}
