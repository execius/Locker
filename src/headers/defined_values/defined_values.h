#include "includes.h"
#ifndef DEFINED_VALS

#define DEFINED_VALS

#define pwd getenv("HOME")

#define VERSION 1.0
#define HEX_SIZE(BIN_SIZE) 2 * BIN_SIZE + 1
#define CIPHER_SIZE(len, block_size)                       \
  len + (block_size - (len % block_size))

#ifdef _WIN32
#include <windows.h>
#define DEFAULT_MAX_PATH 32767
#else
#include <unistd.h>
#define DEFAULT_MAX_PATH 4096
#endif

/*gets the maximum file lenght depending on the
 * os */
size_t get_system_max_path(void);

typedef enum constant_values {
  NUMBER_OF_ENCRYPTION_OPTIONS = 6,
  JSON_OVERHEAD_SIZE =
      4, // for two brackets ans newlinw chars
  /*used for parsing the json thar contain the cipher
            of the account */
  STORED_JSON_LINES = 4,
  MAXLEN = 4096,    // maximum string lengh
  MAXNUMBER = 9999, // maximum int value
  NUMBER_OF_INIT_VARS =
      4, // number of thing that we will ask the user for in
         // the initialization
  SHA256_SALT_SIZE = 16,
  SHA256_HASH_SIZE_BYTES = 32,
  KEY_SIZE_256 = 32,
  AES_256_BLOCK_SIZE = 16,
  MAX_CIPHER_SIZE = MAXLEN + (16 - (MAXLEN % 16)),
  SHA256_SALT_SIZE_HEX = 2 * SHA256_SALT_SIZE + 1,
  SHA256_HASH_SIZE_HEX = 2 * SHA256_HASH_SIZE_BYTES + 1,
  RIPEMD160_KEY_SIZE_BYTES = 32,
  RIPEMD160_SALT_SIZE_BYTES = 16,
  ACCOUNT_MAX_SIZE = 8 * MAXLEN + sizeof(int),
  CIPHER_ACCOUNT_MAX_SIZE =
      8 * (MAXLEN + (16 - (MAXLEN % 16)) + sizeof(int)),
} values;

int define_paths(char *Locker_folder, char *users_folder,
                 char *configs_folder,
                 char *accounts_folder, size_t maxlen,
                 char *PWD);
#endif // !DEFINED_VALS
