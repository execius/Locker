#include "includes.h"

#ifndef ACC_JSON_H
#define ACC_JSON_H

int account_to_json(account *accc, cJSON *json_obj );
int json_to_account(cJSON *json_obj ,account *accc );
#endif // !ACC_JSON_H
