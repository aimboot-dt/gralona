#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "repos.h"
#include "open_repo_list.h"

Repo repos[MAX_REPOS];
int repo_count = 0;

void load_repos() {
    FILE* fp = open_repo_list();
    if (!fp) {
        perror("Failed to open repos.list");
        return;
    }

    char line[600];
    while (fgets(line, sizeof(line), fp) && repo_count < MAX_REPOS) {
        if (line[0] == '#' || line[0] == '\n' || line[0] == '\0') continue;

        char *start = strchr(line, '[');
        char *end = strchr(line, ']');
        if (!start || !end || end < start) continue;

        int name_len = end - start - 1;
        if (name_len >= sizeof(repos[repo_count].name)) continue;

        strncpy(repos[repo_count].name, start + 1, name_len);
        repos[repo_count].name[name_len] = '\0';

        char *url_start = end + 1;
        while (*url_start == ' ' || *url_start == '\t') url_start++;

        // Remove trailing newline
        char *newline = strchr(url_start, '\n');
        if (newline) *newline = '\0';

        strncpy(repos[repo_count].url, url_start, sizeof(repos[repo_count].url) - 1);
        repos[repo_count].url[sizeof(repos[repo_count].url) - 1] = '\0';

        repo_count++;
    }

    fclose(fp);
}

