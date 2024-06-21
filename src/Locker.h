#include "includes.h"

// #include <stdio.h>
// #include <stdlib.h>
// #include "initialize.h"
// #include "account_utils.h"
// #include "defined_values.h"
// #include "configs.h"
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

    printf("%s\n %s\n %s\n %s\n %d\n",accc.array[USERINDEX],accc.array[EMAILINDEX],accc.array[PASSWORDINDEX],accc.array[PLATFORMINDEX],*accc.accountnumber);
    changemember(&accc,0,"99",INT_TYPE);
    changemember(&accc,USERINDEX,"newname",CHAR_TYPE);
    printf("%s\n %s\n %s\n %s\n %d\n",accc.array[USERINDEX],accc.array[EMAILINDEX],accc.array[PASSWORDINDEX],accc.array[PLATFORMINDEX],*accc.accountnumber);
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

int testparse(){
  int eror_tracker = 0;
  pair **array = malloc(4*sizeof(pair ));
  FILE *file_pointer = fopen(USER_CONFIG_FILE,"r");

  if(NULL == file_pointer){//checking if the file has been successfully opened
    log_error("error: could not open file " );
    return ERROR_FILE_OPENING_FAILED;
  }

  for(int i = 0 ; i<NUMBER_OF_CONFIG_INFORMATION;i++){
    array[i] = malloc(sizeof(pair));
  }

  if (SUCCESS == (eror_tracker = parse_file(file_pointer ,array,LINE_MAX_LENGHT,MAXLEN,NUMBER_OF_CONFIG_INFORMATION)))
     for(int i = 0 ; i<NUMBER_OF_CONFIG_INFORMATION;i++){
    printf("key : %s \nvalue : %s \n",array[i]->key,array[i]->value);
  }
  for(int i = 0 ; i<NUMBER_OF_CONFIG_INFORMATION;i++){
   free_pair(array[i]);
   free(array[i]);
  }
  free(array);
  return SUCCESS;
}
int testjson(){
  account *accc = malloc(sizeof(account )) ;
  int error_tracker;
  cJSON *json = cJSON_CreateObject();
  if (SUCCESS != (error_tracker = initialize_account(accc))){
    log_error("could not initialize account , locker.h");
    return error_tracker;
  }
  for(int i = 0 ; i<NUMBEROFINFO;i++){
      printf("%d>",i);
      fgets(accc->array[i],MAXLEN,stdin);}

  if (SUCCESS != (error_tracker = account_to_json(accc,json))){
    log_error("account to json eror");
    return error_tracker;
  }
  char *string = cJSON_Print(json);
  printf("%s\n",string);
  free(string);

  account *acc2 = malloc(sizeof(account));
  if (SUCCESS != (error_tracker = initialize_account(acc2))){
    log_error("could not initialize account , locker.h");
    return error_tracker;
  }
  json_to_account(json,acc2);
  printaccount(*acc2);
  free_account(accc);
  free_account(acc2);
  free(acc2);
  free(accc);
  cJSON_Delete(json);
  return SUCCESS;
}
