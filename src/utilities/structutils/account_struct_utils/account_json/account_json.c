#include "account_json.h"
int account_to_json(account *accc, cJSON *json_obj ){
  int error_tracker;
  /* cheking if the account object is initialized*/
  if(SUCCESS != (error_tracker = isinitialized(accc))){ 
    log_error("error: uninitialized account , function :account_to_json");
    return error_tracker;
  }
  /*check if the alocation of the cJSON object went good*/
  if (NULL == json_obj){
    log_error("JSON object creation failed , function : account_to_json");
    return ERROR_JSON_OBJECT_CREATION;
  }

  /*making a json object and linking each string in the account's array struct to a item within the json object*/
  for(int i =0;i<NUMBEROFINFO;++i){
    switch (i) {
      case USERINDEX:
        if (NULL == cJSON_AddStringToObject(json_obj, "user", *(accc->array+USERINDEX))){
          log_error("in funtion account_to_json , null value while adding a string to json object");
          return ERROR_JSON_ADDING_ITEM_TO_OBJ;/*checking for errors*/
        }
        break;
      case EMAILINDEX:
        if (NULL == cJSON_AddStringToObject(json_obj, "email", *(accc->array+EMAILINDEX))){
          log_error("in funtion account_to_json , null value while adding a string to json object");
          return ERROR_JSON_ADDING_ITEM_TO_OBJ;/*checking for errors*/
        }
        break;
      case PASSWORDINDEX:
        if (NULL == cJSON_AddStringToObject(json_obj, "password", *(accc->array+PASSWORDINDEX))){
          log_error("in funtion account_to_json , null value while adding a string to json object");
          return ERROR_JSON_ADDING_ITEM_TO_OBJ;/*checking for errors*/
        }
        break;
      case PLATFORMINDEX:
        if (NULL == cJSON_AddStringToObject(json_obj, "platform", *(accc->array+PLATFORMINDEX))){
          log_error("in funtion account_to_json , null value while adding a string to json object");
          return ERROR_JSON_ADDING_ITEM_TO_OBJ;/*checking for errors*/
        }
        break;
      default:
        log_error("in funtion account_to_json , index out of bounds while adding account info to json object");
        return ERROR_JSON_ADDING_ITEM_TO_OBJ;

    }
  }
  /*make the account number into an item in the json object*/
  if (cJSON_AddNumberToObject(json_obj, "accountnumber", *accc->accountnumber) == NULL){
    log_error("in funtion account_to_json , null value while adding a integer to json object");
    return ERROR_JSON_ADDING_ITEM_TO_OBJ;
  }
  return SUCCESS;
}


int json_to_account(cJSON *json_obj ,account *accc ){
  int error_tracker;
  /* cheking if the account object is initialized*/
  if(SUCCESS != (error_tracker = isinitialized(accc))){ 
    log_error("error: uninitialized account , function : json_to_account");
    return error_tracker;
  }
  /*check if the alocation of the cJSON object went good*/
  if (NULL == json_obj){
    log_error("JSON object creation failed , function : json_to_account");
    return ERROR_JSON_OBJECT_CREATION;
  }


  for(int i =0;i<NUMBEROFINFO;++i){
    switch (i) {
      case USERINDEX:
        if (!cJSON_IsString(cJSON_GetObjectItemCaseSensitive(json_obj, "user"))){
          log_error("eror getting user string from json to account , funtion : json_to_account");
          return ERROR_STDLIB_FUNTION_FAILURE;
        }

        if(!cJSON_GetObjectItemCaseSensitive(json_obj, "user")->valuestring){
          log_error("in funtion json_to_account , null value in the user item's value string");
          return ERROR_NULL_JSON_ITEM;
        }
        if (MAXLEN <= strlcpy(*(accc->array+USERINDEX),cJSON_GetObjectItemCaseSensitive(json_obj, "user")->valuestring,MAXLEN)){
          log_error("in function json_to_account , strlcpy failed");
          return ERROR_STDLIB_FUNTION_FAILURE;
        }
        break;


      case EMAILINDEX:
        if (!cJSON_IsString(cJSON_GetObjectItemCaseSensitive(json_obj, "email"))){
          log_error("eror getting email string from json to account , funtion : json_to_account");
          return ERROR_STDLIB_FUNTION_FAILURE;
        }

        if(!cJSON_GetObjectItemCaseSensitive(json_obj, "email")->valuestring){
          log_error("in funtion json_to_account , null value in the email item's value string");
          return ERROR_NULL_JSON_ITEM;
        }
        if (MAXLEN <= strlcpy(*(accc->array+EMAILINDEX),cJSON_GetObjectItemCaseSensitive(json_obj, "email")->valuestring,MAXLEN)){
          log_error("in function json_to_account , strlcpy failed");
          return ERROR_STDLIB_FUNTION_FAILURE;
        }
        break;


      case PASSWORDINDEX:
        if (!cJSON_IsString(cJSON_GetObjectItemCaseSensitive(json_obj, "password"))){
          log_error("eror getting password string from json to account , funtion : json_to_account");
          return ERROR_STDLIB_FUNTION_FAILURE;
        }

        if(!cJSON_GetObjectItemCaseSensitive(json_obj, "password")->valuestring){
          log_error("in funtion json_to_account , null value in the password item's value string");
          return ERROR_NULL_JSON_ITEM;
        }
        if ( MAXLEN <= strlcpy(*(accc->array+PASSWORDINDEX),cJSON_GetObjectItemCaseSensitive(json_obj, "password")->valuestring,MAXLEN)){
          log_error("in function json_to_account , strlcpy failed");
          return ERROR_STDLIB_FUNTION_FAILURE;
        }
          break;



          case PLATFORMINDEX:

            if (!cJSON_IsString(cJSON_GetObjectItemCaseSensitive(json_obj, "platform"))){
              log_error("eror getting platform string from json to account , funtion : json_to_account");
              return ERROR_STDLIB_FUNTION_FAILURE;
            }

            if(!cJSON_GetObjectItemCaseSensitive(json_obj, "platform")->valuestring){
              log_error("in funtion json_to_account , null value in the platform item's value string");
              return ERROR_NULL_JSON_ITEM;
            }
            if ( MAXLEN <= strlcpy(*(accc->array+PLATFORMINDEX),cJSON_GetObjectItemCaseSensitive(json_obj, "platform")->valuestring,MAXLEN)){
              log_error("in function json_to_account , strlcpy failed");
              return ERROR_STDLIB_FUNTION_FAILURE;}
              break;


              default:
                log_error("in funtion json_to_account , index eror while getting a string from  json object");
                return ERROR_JSON_GETTING_ITEM_TO_OBJ;    }
        }

        if(!cJSON_IsNumber(cJSON_GetObjectItemCaseSensitive(json_obj,"accountnumber"))){
          log_error("in funtion json_to_account , non int value while getting a int from  json object");
          return ERROR_JSON_GETTING_ITEM_TO_OBJ;  }
        *accc->accountnumber = cJSON_GetObjectItemCaseSensitive(json_obj,"accountnumber")->valuedouble;

        return SUCCESS;
}
