#include "configs.h"

int lineparse(char*infotype,char *infovalue,char *line){
  if (NULL == line || NULL == infotype || NULL == infovalue ){//check if newval isnt NULL 
                                                              //memory for all the char * args should be allocated
    log_error("error: NULL value given , function: lineparse");
    return ERROR_NULL_VALUE_GIVEN ;
  }
  int lenght=0;
  while('#' != *line && '\0' == *line && lenght< MAXLEN){//skipping untill a # is spotted
    line++;
    lenght++;
    continue;
  }
  if(*line == '\0'){//no # is found
    log_error("error: empty line given , function: lineparse");
    return ERROR_EMPTY_STRING ;

  }

  lenght = 0;
  if(*line == '#'){//scanning into infotype after # is found until a = is found
    while('\0' != *line && '=' != *line  && lenght< MAXLEN){
      if(' ' == *line || '\b' == *line ||'\t' == *line  )
        continue;

      *(infotype+lenght++) = *line++;

    }
  }
  if(lenght > MAXLEN){//checking if the lengh wasnt bigger then MAXLEN
    log_error("error: infotype too long , function: lineparse");
    return ERROR_TOO_LONG_STRING;
  }
  lenght= 0;

  if(*line == '='){//scanning into infovalue after = is found until a ; is found
    while(';' != *line && lenght< MAXLEN){
      if(' ' == *line || '\b' == *line ||'\t' == *line  )//skipping blanks,tabs and spaces
        continue;
      *(infovalue+lenght++) = *line++;

    }
  }
  if(lenght > MAXLEN){//checking if the lengh wasnt bigger then MAXLEN
    log_error("error: infotype too long , function: lineparse");
    return ERROR_TOO_LONG_STRING;
  }

   return SUCCESS;


}



int scantext(char *buffer ){ 
  //each the buffer has NUMBER_OF_CONFIG_INFORMATION lines
//each line has infotype and infovalue , each of maximum lengh MAXLEN plus # and ; (2*MAXLEN +2)
  char *line;
  FILE *config_file_pointer = fopen(user_config_file,"r");
  if(NULL == Iconfig_file_pointer){
    log_error("error: could not open file  , function: lineparse");
    return ERROR_FILE_OPENING_FAILED;
  }
  while(fgets(line,LINE_MAX_LENGHT,config_file_pointer)){

  }

}
