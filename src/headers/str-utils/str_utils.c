#include "str_utils.h"

int skiptochar(char *tracker, char *str, char character,
               int maxlengh) {

  if (NULL == str ||
      NULL == tracker) { // check for NULL values
    log_error(
        "error: null value given , function: skiptochar");
    return ERROR_NULL_VALUE_GIVEN;
  }
  int lenght =
      0; // lengh tracker not to excede the maximum lenght

  while (character != *str && '\0' != *str &&
         lenght < maxlengh) {
    /*skipping untill a # or a null char is spotted
  or the lenght limit is exceded*/
    str++;
    lenght++;
    continue;
  }
  if (lenght >= maxlengh) { // checking if the string lenght
                            // is within bounds
    log_error("error: key too long , function: trimspaces");
    return ERROR_TOO_LONG_STRING;
  }

  if (*str == '\0') { // no # is found and the string ended
    log_error(
        "error: empty string given , function: skiptochar");
    return ERROR_EMPTY_STRING;
  }
  tracker = str;
  return SUCCESS;
}

int trimspaces(char *str, int maxlengh) {
  if (NULL == str) { // check for NULL values
    log_error(
        "error: null value given , function: trimspaces");
    return ERROR_NULL_VALUE_GIVEN;
  }

  int lenght = 0;
  while ('\0' != *str && isspace(*str) &&
         lenght < maxlengh) {
    /*skipping untill a non-space or a null char is spotted
  or the lenght limit is exceded*/
    str++;
    lenght++;
    continue;
  }
  if (*str == '\0') { // the string ended
    log_error(
        "error: target character mot found and a null "
        "character reached, function: trimspaces");
    return ERROR_CHAR_NOT_FOUND;
  }
  lenght = 0;
  int stringlen = strlen(str);

  if (stringlen >= maxlengh) { // checking if the string
                               // lenght is within bounds
    log_error("error: key too long , function: trimspaces");
    return ERROR_TOO_LONG_STRING;
  }

  while (isspace(str[stringlen])) {
    stringlen--;
    continue;
  }
  str[stringlen + 1] = '\0';
  return SUCCESS;
}

int scan_to_char(char *dest, char *src, char character,
                 int maxlengh) {
  if (!src || !dest) { // check for NULL values
    log_error(
        "error: null value given , function: scan_to_char");
    return ERROR_NULL_VALUE_GIVEN;
  }

  int lenght = 0;
  while ('\0' != *src && character != *src &&
         lenght <= maxlengh) {

    if (isspace(*src)) { // skipping blanks,tabs and spaces
      src++;
      continue;
    }
    *(dest + lenght++) = *src++;
  }
  if (lenght >= maxlengh) {
    log_error("error: key too long , function: trimspaces");
    return ERROR_TOO_LONG_STRING;
  }

  if (lenght == 0)
    return ERROR_EMPTY_STRING;

  if ('\0' == *src) {
    return ERROR_CHAR_NOT_FOUND;
    log_error(
        "error: target character mot found and a null "
        "character reached, function: scan_to_char");
  }
  *(dest + lenght) = '\0';

  return SUCCESS;
}
