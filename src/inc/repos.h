#ifndef REPOS_H
#define REPOS_H

#define MAX_REPOS 32
#include "package_parser.h"
#include "stddef.h"
void load_repos(void);

typedef struct {
    char name[128];
    char url[2048];
    char pkg_file_list[4109];
    size_t pkg_count;
    Package* packages;
} Repo;

extern Repo repos[MAX_REPOS];
extern int repo_count;
int search_for_repo(const char *name);
size_t count_packages(const char *filepath);
int parse_packages(const char *filepath, Package* packages, size_t pkg_count);
int load_repo_package_list(Repo *repo);
int load_repo_packages(Repo *repo);
#endif

