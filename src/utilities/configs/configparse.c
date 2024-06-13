#include "configparse.h"

int lineparse(char*infotype,char *infovalue,char *line){
  if (NULL == line || NULL == infotype || NULL == infovalue ){//check if newval isnt NULL 
                                                              //memory for all the char * args should be allocated
    log_error("error: NULL value given , function: lineparse");
    return ERROR_NULL_VALUE_GIVEN ;
  }
  int i=0;
  while('#' != *line && '\0' == *line && i< MAXLEN){
    line++;
    i++;
    continue;
  }
  if(*line == '\0'){
    log_error("error: empty line given , function: lineparse");
    return ERROR_EMPTY_STRING ;

  }

  i = 0;
  if(*line == '#'){
    while('\0' != *line && '=' != *line  && i< MAXLEN){
      *(infotype+i++) = *line++;

    }
  }
  i= 0;
  if(*line == '='){
    while('\0' != *line && '\0' != *line  && i< MAXLEN){
      *(infotype+i++) = *line++;

    }
  }
   return SUCCESS;


}
