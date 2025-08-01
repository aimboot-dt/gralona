#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "repos.h"



char* repo_urls[MAX_REPOS];
int repo_count = 0;

void load_repos(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        perror("Failed to open repos.list");
        return;
    }

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), fp) && repo_count < MAX_REPOS) {
        line[strcspn(line, "\n")] = '\0'; // trim newline
        if (line[0] == '\0' || line[0] == '#') continue; // skip empty or comment lines

        repo_urls[repo_count] = strdup(line); // strdup needs <string.h>
        repo_count++;
    }

    fclose(fp);
}

