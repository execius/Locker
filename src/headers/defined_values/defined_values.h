#ifndef DEFINED_VALUES
#define DEFINED_VALUES


enum constant_values{
 NUMBEROFINFO = 4, //number of infos in the accounts struct
 USERINDEX = 0,
 EMAILINDEX = 1,
 PASSWORDINDEX = 2,       //indexes of different information in the array inside account struct
 PLATFORMINDEX = 3,
 NUMBER_OF_CONFIG_INFORMATION = 4, 
 MAXLEN = 4096,      //maximum string lengh
 MAXNUMBER = 9999,   //maximum int value
 NUMBER_OF_INIT_VARS = 4, //number of thing that we will ask the user for in the initialization
 SHA256_SALT_SIZE = 16,
 SHA256_HASH_SIZE_BYTES = 32,
 KEY_SIZE_256 = 32,
 AES_256_BLOCK_SIZE = 16,
 MAX_CIPHER_SIZE = MAXLEN+(16-(MAXLEN%16))
};

#endif 
