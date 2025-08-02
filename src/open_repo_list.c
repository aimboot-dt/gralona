#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REPOS_LIST_PATH_LEN 512

FILE *open_repos_list() {
    const char *home = getenv("HOME");
    if (!home) {
        fprintf(stderr, "HOME environment variable not set.\n");
        return NULL;
    }

    char path[REPOS_LIST_PATH_LEN];
    snprintf(path, sizeof(path), "%s/.local/gralona/repos.list", home);

    FILE *f = fopen(path, "r");
    if (!f) {
        perror("Failed to open repos.list");
        return NULL;
    }

    return f;
}
