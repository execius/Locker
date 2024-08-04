#include "config_writer.h"
/*take a key and a value and makes a parsable 
 line out of them  */
int make_config_line(char *line,
                     char *key,
                     char* value
                     ,size_t str_maxlen)
{

  /*removing newline character*/
  key[strcspn(key, "\n")] =  '\0';
  value[strcspn(value, "\n")] =  '\0';

  if (NULL == line ||
    NULL == key ||
    NULL == value )
    return ERROR_NULL_VALUE_GIVEN; 
  if(0 > sprintf(line, "#%s=%s;", key,value))
    return ERROR_STDLIB_FUNTION_FAILURE;;
  return SUCCESS;
}
/*takes a string config line and writes it 
 to a config file*/
int write_config_line(
  char *config_file,
  char *line
  ,size_t line_maxlen
  ,size_t path_maxlen
){
  FILE *file;
  if(!config_file || !line){
    log_error(
      "null string given , in funtion : write_config_line"
    );
    return ERROR_NULL_VALUE_GIVEN;
  }/*just checking for null values*/

/*writing to the file*/
  if(NULL == (file = fopen(config_file,"a")))
    return ERROR_CANNOT_WRITE_TO_FILE;

  if (0 > fprintf(file, "%s\n",line))\
  {
    log_error("write_config_line: error occurred writing to the file\n");
    fclose(file);
    return ERROR_STDLIB_FUNTION_FAILURE;
  }
  fclose(file);
  return SUCCESS;
}
/*using the previous funcs , writes a pair struct 
 to a config file */
int write_config_pair(
  char *config_file,
  pair *couple,
  size_t str_maxlen,
  size_t line_maxlen,
  size_t path_maxlen
){
  int err = 0;
  char *line[2*str_maxlen+4];

  if(SUCCESS != (err = pair_isinitialised(couple))){
    log_error(
    "uninitialized pair given ,funtion :write_config_pair"
    );
    return errno;
  }


  if (SUCCESS != (err = make_config_line((char*)line,couple->key,couple->value,str_maxlen)))
    return err;

  if (SUCCESS != (err = write_config_line(config_file,(char *)line,line_maxlen,path_maxlen)))
    return err;


  return SUCCESS;
  }
/* this function writes an array of pair structs into a file
 in the config format of this program*/

int write_array_of_pairs(
  char *user_config_file ,
  pair **array_of_pairs,
  int number_of_configs,
  size_t str_maxlen,
  size_t line_maxlen,
  size_t path_maxlen)
{
  int i = 0; 
  int err = 0;
  while (i < number_of_configs) {
    /*just looping to write each pair */

    if (SUCCESS != (err = write_config_pair(
      user_config_file,
      *(array_of_pairs+i),
      str_maxlen,
      line_maxlen,
      path_maxlen
    )))
      return  err;
    i++;
  }
  return SUCCESS;
}


