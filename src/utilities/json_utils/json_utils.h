#include "includes.h"
#ifndef JSON_UTILS
#define JSON_UTILS

int get_data_into_json(cJSON *json_obj, const char *list[],
                       const char *list_clarifications[],
                       int number_of_inf, size_t maxlen);
int encrypt_json(cJSON *json, cJSON **encrypted_json,
                 unsigned char *username,
                 unsigned char *key,
                 const EVP_CIPHER *(*EVP_CBC_FUNC)(void));
int decrypt_json(cJSON *encrypted_acc_json, cJSON **json,
                 unsigned char *username,
                 unsigned char *key,
                 const EVP_CIPHER *(*EVP_CBC_FUNC)(void));
int free_cjson_array(cJSON **arr, int size);

int modify_item(cJSON *object_to_modify, char *newvalue,
                size_t maxlen);

int modify_json(cJSON *jsontomod, const char *item_name,
                char *newvalue, size_t maxlen);
#endif // DEBUG
