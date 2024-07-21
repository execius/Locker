#include "config_writer.h"
int make_config_line(char *line,char *key,char* value,size_t str_maxlen){
  if (NULL == line ||
    NULL == key ||
    NULL == value )
    return ERROR_NULL_VALUE_GIVEN;
  if(0 > sprintf(line, "#%s=%s;", key,value))
    return ERROR_STDLIB_FUNTION_FAILURE;;
  return SUCCESS;
}
int write_config_line(
  char *config_file,
  char *line
  ,size_t line_maxlen
  ,size_t path_maxlen
){
  FILE *file;
  int err = 0;
  if(!config_file || !line){
    log_error(
      "null string given , in funtion : write_config_line"
    );
    return ERROR_NULL_VALUE_GIVEN;
  }
  if (SUCCESS != file_exists(config_file
                             ,path_maxlen)){
    log_error(
      "eror while writing configs to file , cannot open the file"
    );
    return ERROR_FILE_DOESNT_EXIST;
  }
if(NULL == (file = fopen(config_file,"a")))
    return ERROR_CANNOT_WRITE_TO_FILE;

  if (0 < (err = fprintf(file, "%s\n",line)))
  {
    log_error("write_config_line: error occurred writing to the file\n");
    fclose(file);
    return ERROR_STDLIB_FUNTION_FAILURE;
  }
  fclose(file);
  return SUCCESS;
}

int write_config_pair(
  char *config_file,
  pair *couple,
  size_t str_maxlen,
  size_t line_maxlen,
  size_t path_maxlen
){
  char *line[2*str_maxlen+4];

  if(SUCCESS != pair_isinitialised(couple)){
    log_error(
    "uninitialized pair given ,funtion :write_config_pair"
    );
  }
  if (SUCCESS != make_config_line((char*)line,couple->key,couple->value,str_maxlen))
    return errno;
  if (SUCCESS != write_config_line(config_file,(char *)line,line_maxlen,path_maxlen))
    return errno;
  return SUCCESS;
  }


