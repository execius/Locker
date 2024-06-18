//the eror code is in src/headers/eror_handling/eror_handling.h
//all the globaly defined values are  src/headers/defined_values/defined_values.h

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "eror_handling.h"
#include "defined_values.h"
#include "pair_utils.h"

#ifndef CONF_PARSE
#define CONF_PARSE

#define USER_CONFIG_FILE "/home/qbit/coding/c/cpassremake/src/utilities/configs/configs.cpassmann" 

/*each line has infotype and infovalue , 
each of maximum lengh MAXLEN plus # and 
 (2*MAXLEN +2) = 2*(MAXLEN+1)*/

#define LINE_MAX_LENGHT (2*(MAXLEN+1))

/*
 * parses a key value and a value from a line , 
 * and puts then in a pair struct
 * the line should be in the following format :
 * #key = value; */
int file_to_buffer(char *filename ,char **array_strs ,int (*line_check)(char* ,int),int line_max_len,int str_maxlengh,int max_numberoflines);
int parse_array(char** array_strs, int max_numberoflines,int line_max_len,int str_maxlenght , pair **array_of_pairs,int (*line_check)(char* ,int) ); 
int  linecheck(char *line, int maxlengh);
#endif //CONF_PARSE

