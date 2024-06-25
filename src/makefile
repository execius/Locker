CC=clang

testingstructs :
	$(CC) headers/eror_handling/eror_handling.c	utilities/initialize/initialize.c utilities/structutils/pair_struct_utils/pair_utils.c utilities/structutils/account_struct_utils/account_utils.c  utilities/configs/configs.c ../../cJSON/cJSON.c utilities/structutils/account_struct_utils/account_json/account_json.c Locker.c -I utilities/initialize -I utilities/structutils/account_struct_utils/ -I utilities/structutils/pair_struct_utils/ -I headers/eror_handling   -I utilities/configs/ -I headers/defined_values/ -I headers/includes/  -I utilities/structutils/account_struct_utils/account_json/ -o testinginitialize


optimization_testing :
	$(CC) -O3  headers/eror_handling/eror_handling.c	utilities/initialize/initialize.c utilities/structutils/pair_struct_utils/pair_utils.c utilities/structutils/account_struct_utils/account_utils.c  utilities/configs/configs.c ../../cJSON/cJSON.c utilities/structutils/account_struct_utils/account_json/account_json.c Locker.c -I utilities/initialize -I utilities/structutils/account_struct_utils/ -I utilities/structutils/pair_struct_utils/ -I headers/eror_handling   -I utilities/configs/ -I headers/defined_values/ -I headers/includes/ -I utilities/structutils/account_struct_utils/account_json/ -o testinginitialize

debug :
	$(CC)  -g -Wall  -pedantic -lm headers/eror_handling/eror_handling.c	utilities/initialize/initialize.c utilities/structutils/pair_struct_utils/pair_utils.c utilities/structutils/account_struct_utils/account_utils.c  utilities/configs/configs.c ../../cJSON/cJSON.c utilities/structutils/account_struct_utils/account_json/account_json.c Locker.c -I utilities/initialize -I utilities/structutils/account_struct_utils/ -I utilities/structutils/pair_struct_utils/ -I headers/eror_handling   -I utilities/configs/ -I headers/defined_values/ -I headers/includes/  -I utilities/structutils/account_struct_utils/account_json/ -o testinginitialize


