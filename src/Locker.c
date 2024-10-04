#include "Locker.h"


int main(int argc, char *argv[])
{ 
  /*
   * this handles the commandline arguments*/


  /*keeps track of the commandline options */
  int c;
  /*those will hold the values later for login*/
  char *username,*password;
  username = malloc(MAXLEN*sizeof(char)+1);
  password = malloc(MAXLEN*sizeof(char)+1);

  /*this is a key derived from the password*/
  unsigned char *key ;
  key = malloc(KEY_SIZE_256*sizeof(char));
  /*flags to check if an option is given*/
  int uflg = 0, Pflg = 0, rflg = 0;
  int mflg = 0, vflg = 0,  pflg = 0;
  int iflg = 0, nflg = 0;

  /*getting commandline options and inceasing flags*/
  while ((c = getopt(argc, argv, ":u:P:ar:m:vp:in")) != -1) {
    switch(c) {    
      case 'u':
        uflg++;
        /*if -u get username*/
        strncpy(username,optarg,MAXLEN);
        break;
      case 'P':
        Pflg++;
        /*if -P get password*/
        strncpy(password,optarg,MAXLEN);
        break;
      case 'p':
        pflg++;
        break;
      case 'm':
        mflg++;
        break;
      case 'n':
        nflg++;
        break;
      case 'r':
        rflg++;
        break;
      case 'v':
        vflg++;
        break;
      case 'i':
        iflg++;
        break;
      /*misuse handling*/
      case ':':       
        fprintf(stderr,
                "Option -%c requires an operand\n", optopt);
        return SUCCESS;
        break;
      case '?':
        fprintf(stderr,
                "Unrecognized option: '-%c'\n", optopt);
        return SUCCESS;
        break;
    }
  }
  /*handling flags */


  switch (vflg) {
    case 0:
      break;
    default:
      printf("version %.2f\n",VERSION);
      goto free_stuff;
      return SUCCESS;
      break;

  }
  /*checking that a username and a password were created before preceeding */
  if ((uflg!=1 || Pflg != 1) && iflg == 0){
    log_error("provide one username and one password");
    goto free_stuff;
    return SUCCESS;
  }
  /*initializing the program at first use to create necessary folders and such*/
  if (iflg  != 0){
    simple_initialize();
    goto free_stuff;
    return errno;
  }

/*authentication of the user */

  simple_login(username,password);
  switch (errno) {
    case SUCCESS:
      printf("login success\n");
      break;
    default:
      goto free_stuff;
      return errno;
      break;
  }
  /*creating the encryption key from the user password*/

  hashing_global((const char *)password,
             (const unsigned char*)username,
             SHA256_SALT_SIZE,
             1,
             key,
             KEY_SIZE_256,
             EVP_ripemd160);
  if (SUCCESS != errno){
    goto free_stuff;
    return errno;
  }
  /*handling the creation of a new user*/
  if (nflg  != 0){
    new_account((unsigned char*)username,
                key) ;
    return errno;
  }
free_stuff :
  free(username);
  free(key);
  free(password);
  printf("%d\n",errno);
  return errno;
}
