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
    // log_error("error: empty line given , function: lineparse");
    return ERROR_EMPTY_STRING ;
  }
  if(NULL != strchr(line ,'#') && NULL != strchr(line,'=') && NULL != strchr(line,';')) {
    //checking if the string contains a #,= and ; , so it matches the congig format
    return SUCCESS ;
  }
  else {
    // log_error("invalid config line found");
    return ERROR_INVALID_CONFIG_LINE;
  }
}


int file_to_buffer(char *filename ,char **array_strs ,int (*line_check)(char* ,int),int line_max_len,int str_maxlengh,int max_numberoflines){
  if (NULL == array_strs ){//check for null values 
    log_error("error: null value given , function: file_to_buffer");
    return ERROR_NULL_VALUE_GIVEN ;
  }

  char *line = malloc(line_max_len*sizeof(char));
  if (NULL == line ){//check for NULL values 
    log_error("error: null value given , function: file_to_buffer");
    return ERROR_NULL_VALUE_GIVEN ;
  }

  FILE *file_pointer = fopen(filename,"r");

  if(NULL == file_pointer){
    log_error("error: could not open file  , function: file_to_buffer");
    return ERROR_FILE_OPENING_FAILED;
  }
  int i = 0;
  int error = 0;
  while(  i < max_numberoflines ){
    fgets(array_strs[i],line_max_len,file_pointer);
    if(SUCCESS == line_check(array_strs[i],str_maxlengh)){
      i++;
      continue;}
    
    continue;
  }

  fclose(file_pointer);
  return SUCCESS;

} 






int lineparse(pair *couple ,char *line,int str_maxlengh,int (*line_check)(char* ,int)){
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




int parse_array(char** array_strs, int numberoflines,int line_max_len,int str_maxlenght , pair **array_of_pairs,int (*line_check)(char* ,int) ){ 

  if(NULL == array_of_pairs){ //failed allocation for the array
    log_error("error: configs array not allocated  , function: parsefile");
    return ERROR_NULL_VALUE_GIVEN;}

  int i = 0;
  int error;
  while( i < numberoflines){
      if(SUCCESS != (error = initialize_pair(array_of_pairs[i]))){
      log_error("error: could not initialize pair  , function: parsefile");
      return error;
    }

    if(SUCCESS == (error = lineparse(array_of_pairs[i],array_strs[i],str_maxlenght,linecheck))){
      i++;
      continue;
    }
    else {
      return error;
    }
  }

 
return SUCCESS;

}
