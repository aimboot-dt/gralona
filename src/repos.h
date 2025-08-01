#ifndef REPOS_H
#define REPOS_H

#define MAX_REPOS 10
#define MAX_LINE 256

extern char* repo_urls[MAX_REPOS];
extern int repo_count;

void load_repos(const char* filename);

#endif

