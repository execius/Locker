#include <stdio.h>
#include <stdlib.h>
#include "initialize.h"
#include "struct-utils.h"
#include "defined_values.h"
// int testinitialize() {
//   char **arr = initialize();
//    for (int i = 0 ; i < NUMBER_OF_INIT_VARS ;i++){
//     printf("%s\n",arr[i]);
//
//   }
//    return SUCCESS;
// }
int testeditstruct(){
  account accc;
  if(initialize_account(&accc) == SUCCESS ){
    for(int i = 0 ; i<NUMBEROFINFO;i++){
      printf("%d>",i);
      fgets(accc.array[i],MAXLEN,stdin);}

    printf("%s\n %s\n %s\n %s\n %d\n",accc.array[USERINDEX],accc.array[EMAILINDEX],accc.array[PASSWORDINDEX],accc.array[PLATFORMINDEX],accc.accountnumber);
    changemember(&accc,0,"99",INT_TYPE);
    printf("%s\n %s\n %s\n %s\n %d\n",accc.array[USERINDEX],accc.array[EMAILINDEX],accc.array[PASSWORDINDEX],accc.array[PLATFORMINDEX],accc.accountnumber);
    free_account(&accc);
    return SUCCESS;
  }
  else
    return -1;
}

int testprdup(){
   account acc ;
   account ac;
   int error ;
   if (SUCCESS != ( error = initialize_account(&acc))) return error ;
   if (SUCCESS != ( error = initialize_account(&ac))) return error ;

  for(int i = 0 ; i<NUMBEROFINFO;i++){
      printf("%d>",i);
      fgets(acc.array[i],MAXLEN,stdin);
  }
  *acc.accountnumber = 9;
  if (SUCCESS != (error = accountdup(&acc,&ac)) ) return error;
  free_account(&acc);
  printaccount(ac);
  free_account(&ac);
  return SUCCESS;

}
