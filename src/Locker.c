#include "Locker.h"
int main(int argc, char *argv[])
{ 
  int c;
  char *username,*password;
  username = malloc(MAXLEN*sizeof(char)+1);
  password = malloc(MAXLEN*sizeof(char)+1);
  int uflg = 0, Pflg = 0, rflg = 0;
  int mflg = 0, vflg = 0,  pflg = 0;
  int iflg = 0;
  while ((c = getopt(argc, argv, ":u:P:ar:m:vp:i")) != -1) {
    switch(c) {    
      case 'u':
        uflg++;
        strncpy(username,optarg,MAXLEN);
        break;
      case 'P':
        Pflg++;
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
  switch (vflg) {
    case 0:
      break;
    default:
      printf("version %.2f\n",VERSION);
      return SUCCESS;
      break;

  }
  if ((uflg!=1 || Pflg != 1) && iflg == 0){
    log_error("provide one username and one password");
  }
  if (iflg  != 0){
    simple_initialize();
    free(username);
    free(password);
    return errno;
  }

  
simple_login(username,password);
  switch (errno) {
    case SUCCESS:
      printf("login success\n");
      break;
    default:
      return errno;
      break;
  }
  free(username);
  free(password);
}
