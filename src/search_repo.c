#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include "package_parser.h"
#include "repos.h"
#include "search_for_pkg.h"
Package* binary_search_package_in_repo(Repo *repo, const char *name) {
  int left = 0; int right = repo->pkg_count - 1;
  int mid, cmp;
  while (left <= right) {
    mid = left + (right - left) / 2;
    cmp = strcmp(repo->packages[mid].name, name);

    if(cmp == 0){ return &repo->packages[mid]; } //found 
    else if (cmp < 0) { left = mid + 1;} 
    else { right = mid - 1;}
      
    
    }
  return NULL;
}

Package* search_package_in_repo(Repo *repo, const char *name) {
    
   for (int i = 0; i < repo->pkg_count; i++) {
        if (strcmp(repo->packages[i].name, name) == 0) {
            return &repo->packages[i];  // found
        }
    }
    return NULL;  // not found  
  
}

int install_package_from_repo (Repo *repo, Package* pkg_to_install) {
  if (pkg_to_install == NULL) {fprintf(stderr, "Package not found! try searching for it."); return -1;}
  printf("Installing Package: %s",pkg_to_install->name);
  return 0;
}

