#include "json_utils.h"

int get_data_into_json(cJSON *json_obj,
                const char *list[],
                int number_of_inf,
                size_t maxlen)
{

  char **array_credentials =malloc(number_of_inf*sizeof(char*));
  if(!array_credentials)
    return errno = ERROR_MEMORY_ALLOCATION;
  /*initializing the structs in the array */

  if (NULL == json_obj){
    return errno = ERROR_JSON_OBJECT_CREATION;
  }
  getinfo(list,
          number_of_inf,
          maxlen,
          array_credentials);
  if(SUCCESS != errno )
    return errno;

  for(int i =0;i<number_of_inf;++i){
        if (NULL ==
      cJSON_AddStringToObject(json_obj,
                              list[i], 
                              array_credentials[i])){
          return errno =  ERROR_JSON_ADDING_ITEM_TO_OBJ;/*checking for errors*/
        }
    }
  free_str_array(array_credentials, number_of_inf);
  if(SUCCESS != errno )
    return errno;
  return SUCCESS;
}


