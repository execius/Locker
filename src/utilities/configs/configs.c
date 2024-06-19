#include "configs.h"
/* checks that:
 * the line given is in the corect format (#key=value;)
 * the line is not NULL*/
static int  linecheck(char *line, size_t maxlengh){
  if (NULL == line ){//check for NULL values 
    log_error("error: null value given , function: lineparse");
    return ERROR_NULL_VALUE_GIVEN ;
  }

  if(strchr(line ,'#') && strchr(line,'=') && strchr(line,';')) {
    //checking if the string contains a #,= and ; , so it matches the config format
    return SUCCESS ;
  }
  else {
    // log_error("invalid config line found");    /*for debug*/
    return ERROR_INVALID_CONFIG_LINE;
  }
}


/**
 * scans a the part beween two chars(flags) in a source string into a destinations string
 * be sure the the source contain the flags as it doesnt check and could lead to a segfault
  or overflow if not used properly*/
static int scan_to_char(char *dest , char *src,char start_flag,char end_flag,size_t str_maxlengh){
  size_t lenght = 0;/*to track string lengh not to exceed the maximum lengh*/
  while(start_flag != *(src) ) {/*scanning until the strating flag is found*/
    ++src;
  }
  ++src;

  while(end_flag != *(src+lenght)  && lenght< str_maxlengh){
    /*scanning into the destinations until the end flag is found*/

    *(dest+lenght) = *(src+lenght);
    ++lenght;

  }
  *(dest+lenght) = '\0';


  if(lenght == str_maxlengh){/*checking if the lengh  didnt reach MAXLEN*/
    log_error("error: key too long , function: lineparse");
    return ERROR_TOO_LONG_STRING;
  }
  return SUCCESS;
}

/*parses a config line in the form #key=value; and puts the vkey and value in a pair struct
 * the line should be checked if correct before being passed to this function as it doesnt check*/ 
static int lineparse(pair *couple ,char *line,size_t str_maxlengh){
  size_t lenght = 0;//to keep track of lengh not to exceed the maximum value
  int eror_track = 0; /*to track the values of erors*/
  if ( NULL == couple ||NULL == couple->key || NULL == couple->value ){//check for NULL values 
    log_error("error: null value given , function: lineparse");
    return ERROR_NULL_VALUE_GIVEN ;
  }

  if (SUCCESS != (eror_track = scan_to_char(couple->key,line,'#','=',str_maxlengh))){
    return eror_track;
  }

  if (SUCCESS != (eror_track = scan_to_char(couple->value,line,'=',';',str_maxlengh))){

    return eror_track;
  }

  return SUCCESS ;
}


/*scans a file and returns an array of correctly formated lines in the file ;*/
int parse_file(FILE *file_pointer ,pair **array_of_pairs ,size_t line_max_len,size_t str_maxlengh,size_t max_numberoflines){
  /* the caller of this function should know the maximum number of  config lines are going to be there,
   * set the maximum str lengh for key and value 
   * and set maximum line lengh */
  int error = 0;
  char *line = malloc(line_max_len*sizeof(char*));

  if(NULL == array_of_pairs ){ //checking for null values
    log_error("error: configs array not allocated  , function: parse_file");
    return ERROR_NULL_VALUE_GIVEN;}

  
  int i = 0;
  while( fgets(line,line_max_len,file_pointer) && i < max_numberoflines ){ /*putting the line in the array*/
    switch (linecheck(line,str_maxlengh)) {
      case SUCCESS:
        /*
       * if the line is correctly formated 
       * initialize  a config pair 
       * parsing the line and checking if the line has been successfully parsed*/

        if(SUCCESS != (error = initialize_pair(array_of_pairs[i]))){
          log_error("error: could not initialize pair  , function: parse_file");
          return error;
        }//also checking for errors

        if(SUCCESS == (error = lineparse(array_of_pairs[i],line,str_maxlengh))){

          i++;
          continue;
        }
        else {
          return error;
        }
        i++;
        break;


      default:
        /*if the line is not correctly formated , continue to the next*/
        break;

    }
  } 
  free(line);
  fclose(file_pointer);
  return SUCCESS;
}
