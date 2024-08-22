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

  /*flags to check if an option is given*/
  int uflg = 0, Pflg = 0, rflg = 0;
  int mflg = 0, vflg = 0,  pflg = 0;
  int iflg = 0;

  /*getting commandline options and inceasing flags*/
  while ((c = getopt(argc, argv, ":u:P:ar:m:vp:i")) != -1) {
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
  if ((uflg!=1 || Pflg != 1) && iflg == 0){
    log_error("provide one username and one password");
    goto free_stuff;
    return SUCCESS;
  }
  if (iflg  != 0){
    simple_initialize();
    goto free_stuff;
    return errno;
  }


  simple_login(username,password);
  switch (errno) {
    case SUCCESS:
      printf("login success\n");
      goto free_stuff;
      break;
    default:
      goto free_stuff;
      return errno;
      break;
  }
free_stuff :
  free(username);
  free(password);
}
