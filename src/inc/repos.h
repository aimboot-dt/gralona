#ifndef REPOS_H
#define REPOS_H

#define MAX_REPOS 32


void load_repos(void);

typedef struct {
    char name[128];
    char url[2048];
    char package_list_file[MAX_PATH];
    PackageList packages;
} Repo;

extern Repo repos[MAX_REPOS];
extern int repo_count;

#endif

