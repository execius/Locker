CC=clang

testingstructs :
	$(CC) -lm -lssl -lcrypto -lcjson -lb64 headers/eror_handling/eror_handling.c	utilities/initialize/initialize.c utilities/structutils/pair_struct_utils/pair_utils.c utilities/structutils/account_struct_utils/account_utils.c  utilities/configs/configs.c  utilities/structutils/account_struct_utils/account_json/account_json.c security/encryption/encryptdecrypt.c security/encryption/hashing.c security/login/login.c Locker.c -I utilities/initialize -I utilities/structutils/account_struct_utils/ -I utilities/structutils/pair_struct_utils/ -I headers/eror_handling   -I utilities/configs/ -I headers/defined_values/ -I headers/includes/  -I utilities/structutils/account_struct_utils/account_json/ -I security/encryption/ -I security/login/ -o testinginitialize


optimization_testing :
	$(CC) -O3  -lm -lssl -lcrypto -lcjson -lb64 headers/eror_handling/eror_handling.c	utilities/initialize/initialize.c utilities/structutils/pair_struct_utils/pair_utils.c utilities/structutils/account_struct_utils/account_utils.c  utilities/configs/configs.c  utilities/structutils/account_struct_utils/account_json/account_json.c security/encryption/encryptdecrypt.c security/encryption/hashing.c security/login/login.c Locker.c -I utilities/initialize -I utilities/structutils/account_struct_utils/ -I utilities/structutils/pair_struct_utils/ -I headers/eror_handling   -I utilities/configs/ -I headers/defined_values/ -I headers/includes/  -I utilities/structutils/account_struct_utils/account_json/ -I security/encryption/ -I security/login/ -o testinginitialize

debug :
	$(CC)  -g -Wall  -pedantic -lm -lssl -lcrypto -lcjson -lb64 headers/eror_handling/eror_handling.c	utilities/initialize/initialize.c utilities/structutils/pair_struct_utils/pair_utils.c utilities/structutils/account_struct_utils/account_utils.c  utilities/configs/configs.c  utilities/structutils/account_struct_utils/account_json/account_json.c security/encryption/encryptdecrypt.c security/encryption/hashing.c security/login/login.c Locker.c -I utilities/initialize -I utilities/structutils/account_struct_utils/ -I utilities/structutils/pair_struct_utils/ -I headers/eror_handling   -I utilities/configs/ -I headers/defined_values/ -I headers/includes/  -I utilities/structutils/account_struct_utils/account_json/ -I security/encryption/ -I security/login/ -o testinginitialize


