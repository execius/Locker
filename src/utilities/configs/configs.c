#include "configs.h"
size_t spaceless_strlen(const char *s , int maxlengh) {
  int lentracker = 0 ;//tracker so the string does not exceed the maximum lenght
  size_t len = 0;
  const unsigned char *us = (const unsigned char *) s;
  while (*us && lentracker++ < maxlengh) {
    if (!isspace(*us)) len++;
    us++;
  }
  if (lentracker == maxlengh)
    return ERROR_TOO_LONG_STRING;
  return len;
}


int  linecheck(char *line, int maxlengh){
  if (NULL == line ){//check for NULL values 
    log_error("error: null value given , function: lineparse");
    return ERROR_NULL_VALUE_GIVEN ;
  }
  int lenght=0; //lengh tracker not to excede the maximum lenght 

  if(0 == spaceless_strlen(line ,maxlengh)){//no # is found and the string ended
    log_error("error: empty line given , function: lineparse");
    return ERROR_EMPTY_STRING ;
  }
  if(NULL != strchr(line ,'#') && NULL != strchr(line,'=') && NULL != strchr(line,';')) {
    //checking if the string contains a #,= and ; , so it matches the congig format
    return SUCCESS ;
  }
  else {
    log_error("invalid config line found");
    return ERROR_INVALID_CONFIG_LINE;
  }
}


int lineparse(pair *couple ,char *line,int str_maxlengh){
  int lenght = 0;

  if ( NULL == couple ||NULL == couple->key || NULL == couple->value ){//check for NULL values 
    log_error("error: null value given , function: lineparse");
    return ERROR_NULL_VALUE_GIVEN ;
  }

  if(*line == '#'){//scanning into infotype after # is found until a = is found
    line++;
    while('\0' != *line && '=' != *line  && lenght< str_maxlengh){
      if(isspace(*line)  ){
        line++;
        continue;}

      *(couple->key+lenght++) = *line++;

    }
    *(couple->key+lenght) = '\0';
  }
  printf("%d\n",lenght);
  if(lenght == str_maxlengh){//checking if the lengh wasnt bigger then MAXLEN
    log_error("error: key too long , function: lineparse");
    return ERROR_TOO_LONG_STRING;
  }
  lenght= 0;

  if(*line == '='){//scanning into infovalue after = is found until a ; is found
    line++;
    while(';' != *line && lenght< str_maxlengh){
      if(isspace(*line)  ){//skipping blanks,tabs and spaces
        line++;
        continue;}
      *(couple->value+lenght++) = *line++;

    }
      *(couple->value+lenght) = '\0';
    
  }
  if(lenght == str_maxlengh){//checking if the lengh wasnt bigger then MAXLEN
    log_error("error: value too long , function: lineparse");
    return ERROR_TOO_LONG_STRING;
  }

   return SUCCESS ;


}



int parsefile(char *user_config_file , int number_of_pairs,int line_max_len,int str_maxlenght , pair **configs_array ){ 

  char *line = malloc(line_max_len*sizeof(char));
  if(NULL == line) {//failed allocation for line
    log_error("error:could not allocate memory for 'line', function: parsefile");
    return ERROR_MEMORY_ALLOCATION;}

FILE *config_file_pointer = fopen(user_config_file,"r");

  if(NULL == config_file_pointer){
    log_error("error: could not open file  , function: parsefile");
    return ERROR_FILE_OPENING_FAILED;
  }
  if(NULL == configs_array){ //failed allocation for the array
    log_error("error: configs array not allocated  , function: parsefile");
    return ERROR_NULL_VALUE_GIVEN;}

  int i = 0;
  int error;
  while(fgets(line,line_max_len,config_file_pointer) && i < number_of_pairs ){
    error = 0;
    if(SUCCESS != linecheck(line,str_maxlenght)){
      continue;
    }
    if(SUCCESS == linecheck(line,str_maxlenght)){

      if(SUCCESS != (error = initialize_pair(configs_array[i]))){
      log_error("error: could not initialize pair  , function: parsefile");
      return error;
      }

      if(SUCCESS == (error = lineparse(configs_array[i],line,str_maxlenght))){
        i++;
        continue;
      }
      else {
        return error;
      }
    }
      
  } 
  free(line);
  fclose(config_file_pointer);
  return SUCCESS;
  
}
