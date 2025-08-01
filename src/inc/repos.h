#ifndef REPOS_H
#define REPOS_H

#define MAX_REPOS 32


void load_repos(const char* filename);

typedef struct {
    char name[64];
    char url[512];
} Repo;

extern Repo repos[MAX_REPOS];
extern int repo_count;

#endif

