#include "configs.h"
/* checks that:
 * the line given is in the corect format (#key=value;)
 * the line is not NULL*/
int  linecheck(char *line, int maxlengh){
  if (NULL == line ){//check for NULL values 
    log_error("error: null value given , function: lineparse");
    return ERROR_NULL_VALUE_GIVEN ;
  }

  if(NULL != strchr(line ,'#') && NULL != strchr(line,'=') && NULL != strchr(line,';')) {
    //checking if the string contains a #,= and ; , so it matches the config format
    return SUCCESS ;
  }
  else {
    // log_error("invalid config line found");    /*for debug*/
    return ERROR_INVALID_CONFIG_LINE;
  }
}



/*parses a config line in the form #key=value; and puts the vkey and value in a pair struct
 * the line should be checked if correct before being passed to this function as it doesnt check*/ 
int lineparse(pair *couple ,char *line,int str_maxlengh){
  int lenght = 0;//to keep track of lengh not to exceed the maximum value
  if ( NULL == couple ||NULL == couple->key || NULL == couple->value ){//check for NULL values 
    log_error("error: null value given , function: lineparse");
    return ERROR_NULL_VALUE_GIVEN ;
  }
  while (*line != '#' ) {//skipping until # is found 
    line++;
  }


  if(*line == '#'){//scanning into infotype after # is found     
    line++;//skipping the #

    while('\0' != *line && '=' != *line  && lenght< str_maxlengh){//scanning into the pair's key
      if(isspace(*line)  ){//skipping blanks,tabs and spaces
        line++;
        continue;}

      *(couple->key+lenght++) = *line++;

    }
    *(couple->key+lenght) = '\0';
  }

  if(lenght == str_maxlengh){//checking if the lengh  didnt reach MAXLEN
    log_error("error: key too long , function: lineparse");
    return ERROR_TOO_LONG_STRING;
  }
  lenght= 0;

  while (*line != '=' ) {//skipping until = is found 
    line++;
  }


  if(*line == '='){//scanning into infovalue after = is found until a ; is found
    line++;
    while(';' != *line && lenght< str_maxlengh){//scanning into the pair's value
      if(isspace(*line)  ){//skipping blanks,tabs and spaces
        line++;
        continue;}
      *(couple->value+lenght++) = *line++;

    }
    *(couple->value+lenght) = '\0';

  }
  if(lenght == str_maxlengh){//checking if the lengh  didnt reach MAXLEN
    log_error("error: value too long , function: lineparse");
    return ERROR_TOO_LONG_STRING;
  }

  return SUCCESS ;


}


/*scans a file and returns an array of correctly formated lines in the file ;*/
int parse_file(char *filename ,pair **array_of_pairs ,int line_max_len,int str_maxlengh,int max_numberoflines){
  /* the caller of this function should know the maximum number of  config lines are going to be there,
   * set the maximum str lengh for key and value 
   * and set maximum line lengh */
  char *line = malloc(line_max_len*sizeof(char*));
  
  if(NULL == array_of_pairs ){ //checking for null values
    log_error("error: configs array not allocated  , function: parse_file");
    return ERROR_NULL_VALUE_GIVEN;}

  FILE *file_pointer = fopen(filename,"r");

  if(NULL == file_pointer){//checking if the file has been successfully opened
    log_error("error: could not open file  , function: parse_file");
    return ERROR_FILE_OPENING_FAILED;
  }
  int i = 0;
  int error = 0;

  while( fgets(line,line_max_len,file_pointer) && i < max_numberoflines ){ /*putting the line in the array*/

    if(SUCCESS == linecheck(line,str_maxlengh)){//if the line is correctly formated 
      //initialize  a config pair 
      if(SUCCESS != (error = initialize_pair(array_of_pairs[i]))){
        log_error("error: could not initialize pair  , function: parse_file");
        return error;
      }//also checking for errors

      if(SUCCESS == (error = lineparse(array_of_pairs[i],line,str_maxlengh))){

            i++;
        continue;
      }//parsing the line and checking if the line has been successfully parsed
      else {
        return error;
      }
      i++;
      continue;
    }
    continue;
    /*if the line is not correctly formated , continue to the next*/
  } 
  free(line);
  fclose(file_pointer);
  return SUCCESS;

}
