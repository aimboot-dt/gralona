#include <libgen.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int mkdir_p(const char* path) {
  char tmp[PATH_MAX];
  char *p = NULL;
  size_t len;

  snprintf(tmp, sizeof(tmp), "%s", path);
  len = strlen(tmp);
  if ( tmp[len-1] == '/')  {tmp[len-1] = 0;}
  
  for (p = tmp + 1; *p; p++){
    if (*p == '/') {
      *p = 0;
      if (mkdir(tmp,0755) && errno != EEXIST){
        perror("mkdir_p failed");
        return 1;
      }
    *p = '/';
    }
  }
  if (mkdir(tmp, 0755) && errno != EEXIST) {
    perror("mkdir_p final failed");
    return 1;
  }

  return 0;
}
