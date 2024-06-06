#include <stdio.h>
#include <stdlib.h>
#include "initialize.h"
#include "struct-utils.h"
void testinitialize() {
  char **arr = initialize();
  for (int i = 0 ; i < 2 ;i++){
    printf("%s\n",arr[i]);

  }}
void testeditstruct(){
  struct account accc;
  accc.array[USERINDEX] = "user" ; accc.array[EMAILINDEX] = "email";accc.array[PASSWORDINDEX] ="pass" ; accc.array[PLATFORMINDEX] = "plat";
  accc.accountnumber = 1;
  printf("%s\n %s\n %s\n %s\n %d\n",accc.array[USERINDEX],accc.array[EMAILINDEX],accc.array[PASSWORDINDEX],accc.array[PLATFORMINDEX],accc.accountnumber);
  changemember(&accc,USERINDEX,"NEWUSER","char");
  printf("%s\n %s\n %s\n %s\n %d\n",accc.array[USERINDEX],accc.array[EMAILINDEX],accc.array[PASSWORDINDEX],accc.array[PLATFORMINDEX],accc.accountnumber);
}
