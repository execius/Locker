//the eror code is in src/headers/eror_handling/eror_handling.h
//all the globaly defined values are  src/headers/defined_values/defined_values.h


#include "includes.h"

#ifndef INITIALIZE_H
#define INITIALIZE_H


int getinfo(const char* listofwantedinfo[] ,
            int numberofinfos , 
            int maxlengh ,
            pair **listofanswers);


int initialize_user(const char *list_of_wanted_inf[MAXLEN],
               int number_of_inf,
               int maxlengh,
               size_t bin_hash_len,
               size_t bin_salt_len,
               size_t hex_hash_len,
               size_t hex_salt_len,
               size_t line_maxlen,
               size_t path_maxlen,
               int numbr_of_dirs
               );
int init_dirs(
  char **dirs_paths,
  int number_of_dirs,
  size_t maxlengh);

#endif
