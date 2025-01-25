/*this file is fo globaly defined arrays and the
 counts of their elements*/
#include "arrays_counters.h"

const char *list_of_config_parameters[] = {"encryption"};

const char *account_creds_list[] = {"user", "email",
                                    "password"};

/*make sure to increase the number of initialization info
 if the .h file whenever you add a new element to this
 list*/

const char *list_of_configs_clarifications[] = {
    "you can chose one of those encryption scheme that \
will be used to encrypt your accounts :\n\n\t\
1) AES-256 \n\t2) AES-192\n\t3) AES-128\n\t4) \
CAMELIA 128\n\t5) CAMELIA 192\n\t6) CAMELIA 256\n\t\
",
    "blah blah"};

const char *list_of_accounts_clarifications[] = {
    "enter the username", "enter the email or a equivalent",
    "enter the password"};

const size_t NUMBER_OF_CONFIGS =
    sizeof(list_of_config_parameters) / sizeof(char *);
const size_t NUMBER_OF_DIRS = 4;
const size_t ACCOUNTS_INFO =
    sizeof(account_creds_list) / sizeof(char *);
