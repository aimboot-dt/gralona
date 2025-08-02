#include "repos.h"
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "refresh.h"

const char *home = getenv("HOME");

void refresh_cache_all() {
    for (int i = 0; i < repo_count; ++i) {
        char folder[128];
        snprintf(folder, sizeof(folder), "%s/.local/gralona/cache/%s", home, repos[i].name);

        // Make folder if it doesn't exist
        if (access(folder, F_OK) != 0) {
            mkdir(folder, 0755);
        }

        // Download the Packages.gz file
        char out_file[256];
        snprintf(out_file, sizeof(out_file), "%s/Packages.gz", folder);

        char cmd[1024];
        snprintf(cmd, sizeof(cmd), "curl -fsSL '%s' -o '%s'", repos[i].url, out_file);
        printf("Refreshing: %s\n", repos[i].name);
        int ret = system(cmd);
        if (ret != 0) {
            fprintf(stderr, "Failed to refresh %s\n", repos[i].name);
        }
    }
}
