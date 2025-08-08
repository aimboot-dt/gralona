#ifndef REPOS_H
#define REPOS_H

#define MAX_REPOS 32
#include "package_parser.h"

void load_repos(void);

typedef struct {
    char name[128];
    char url[2048];
    char pkg_file_list[4109];
    int pkg_count;
    Package* packages;
} Repo;

extern Repo repos[MAX_REPOS];
extern int repo_count;

#endif

