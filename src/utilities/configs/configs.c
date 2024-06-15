#include "configs.h"
int  linecheck(char *line){
if (NULL == line ){//check for NULL values 
    log_error("error: null value given , function: lineparse");
    return ERROR_NULL_VALUE_GIVEN ;
  }
  int lenght=0; //lengh tracker not to excede the maximum lenght 

  while('#' != *line && '\0' == *line && lenght< MAXLEN){//skipping untill a # or a null char is spotted , or the lenght limit is exceded
    line++;
    lenght++;
    continue;
  }
  if(*line == '\0'){//no # is found and the string ended
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
int lineparse(pair *couple ,char *line){
  int lenght = 0;



  if ( NULL == couple ||NULL == couple->key || NULL == couple->value ){//check for NULL values 
    log_error("error: null value given , function: lineparse");
    return ERROR_NULL_VALUE_GIVEN ;
  }

  if(*line == '#'){//scanning into infotype after # is found until a = is found
    line++;
    while('\0' != *line && '=' != *line  && lenght< MAXLEN-1){
      if(' ' == *line || '\b' == *line ||'\t' == *line  ){
        line++;
        continue;}

      *(couple->key+lenght++) = *line++;

    }
    *(couple->key+lenght) = '\0';
  }
  if(lenght > MAXLEN){//checking if the lengh wasnt bigger then MAXLEN
    log_error("error: key too long , function: lineparse");
    return ERROR_TOO_LONG_STRING;
  }
  lenght= 0;

  if(*line == '='){//scanning into infovalue after = is found until a ; is found
    line++;
    while(';' != *line && lenght< MAXLEN){
      if(' ' == *line || '\b' == *line ||'\t' == *line  ){//skipping blanks,tabs and spaces
        line++;
        continue;}
      *(couple->value+lenght++) = *line++;

    }
      *(couple->value+lenght) = '\0';
    
  }
  if(lenght > MAXLEN){//checking if the lengh wasnt bigger then MAXLEN
    log_error("error: value too long , function: lineparse");
    return ERROR_TOO_LONG_STRING;
  }

   return SUCCESS ;


}



int parsefile(char *user_config_file , int number_of_pairs,int line_max_len , pair **configs_array ){ 

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
    if(SUCCESS != linecheck(line)){
      continue;
    }
    if(SUCCESS == linecheck(line)){

      if(SUCCESS != (error = initialize_pair(configs_array[i]))){
      log_error("error: could not initialize pair  , function: parsefile");
      return error;
      }

      if(SUCCESS == (error = lineparse(configs_array[i],line))){
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
