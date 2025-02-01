#include "strutils.h"

int free_array(void **arr, int size) {
  if (!arr)
    return ERROR_NULL_VALUE_GIVEN;

  for (int i = 0; i < size; i++) {
    if (NULL != arr[i])
      free(arr[i]);
  }
  free(arr);
  return errno = SUCCESS;
}
void clear_terminal(void) {
#ifdef _WIN32
  system("cls"); // Windows command to clear the screen
#else
  system("clear"); // Unix/Linux/Mac command to clear the
                   // screen
#endif
}

void handle_cjson_error(void) {
  const char *error_ptr = cJSON_GetErrorPtr();
  if (error_ptr != NULL) {
    fprintf(stderr, "Error before: %s\n", error_ptr);
  }
  errno = ERROR_CJSON_LIB_FAILURE;
}

int read_lines(unsigned char *dst, FILE *file,
               int num_lines, int maxlen) {
  if (NULL == file || NULL == dst) {
    return errno = ERROR_NULL_VALUE_GIVEN; // Invalid file
                                           // pointer or
                                           // line count
  }
  if (num_lines <= 0)
    return num_lines;

  char line[MAXLEN] = "";
  int line_count = 0;

  while (line_count < num_lines) {
    if (fgets(line, sizeof(line), file) != NULL) {
      strncat((char *)dst, line,
              maxlen); // Print or process each line here
      line_count++;
      continue;
    }
    break;
  }

  // Check if we read exactly the requested number of lines
  return line_count == num_lines
             ? errno = SUCCESS
             : (errno = ERROR_BAD_ARGUMENT);
}

// Case-insensitive substring search function
const char *stristr(const char *haystack,
                    const char *needle) {
  if (!haystack || !needle || !*needle) {
    return NULL; // Handle NULL or empty strings safely
  }
  const char *h = haystack;
  const char *n;

  while (*h) {
    const char *h_start = h;
    n = needle;

    // Compare characters case-insensitively
    while (*h && *n &&
           tolower((unsigned char)*h) ==
               tolower((unsigned char)*n)) {
      h++;
      n++;
    }
    if (!*n) {
      return h_start;
    }

    h = h_start + 1; // Move to next character in haystack
  }

  return NULL; // No match found
}

/*those are used to hide the text when getting a password*/
void disable_echo(struct termios *oldt, struct termios *newt) {
    tcgetattr(STDIN_FILENO, oldt);  
    *newt = *oldt;
    newt->c_lflag &= ~(ECHO);        
    tcsetattr(STDIN_FILENO, TCSANOW, newt);  
}

void restore_echo(struct termios *oldt) {
    tcsetattr(STDIN_FILENO, TCSANOW, oldt);  
}

