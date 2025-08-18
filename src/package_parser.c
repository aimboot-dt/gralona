#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "package_parser.h"
#include "repos.h"
#include "mkdir_p.h"

#define MAX_LINE 1024

size_t count_packages(const char *filepath) {
    FILE *fp = fopen(filepath, "r");
    if (!fp) return 0;

    char line[MAX_LINE];
    size_t count = 0;
    while (fgets(line, sizeof(line), fp)) {
        // Compare only first 8 chars (to optimize a bit)
        if (strncmp(line, "Package:", 8) == 0) {
            count++;
        }
    }
    fclose(fp);
    return count;
}

int parse_packages(const char *filepath, Package* packages, size_t pkg_count) {
    FILE *fp = fopen(filepath, "r");
    if (!fp) return -1;

    char line[MAX_LINE];
    size_t index = 0;
    Package current = {0};

    while (fgets(line, sizeof(line), fp)) {
        if (strcmp(line, "\n") == 0 || strcmp(line, "\r\n") == 0) {
            if (current.name[0] != '\0') {
       	        if (index >= pkg_count) { break; }
                packages[index++] = current;
                memset(&current, 0, sizeof(Package));
            }
            continue;
        }

        if (strncmp(line, "Package:", 8) == 0) { sscanf(line + 8, "%s", current.name);}
      	else if (strncmp(line, "Version:", 8) == 0) { sscanf(line + 8, "%s", current.version);}
      	else if (strncmp(line, "Filename:", 9) == 0) { sscanf(line + 9, "%s", current.filename);}
      	else if (strncmp(line, "Description:", 12) == 0) { sscanf(line + 12, "%s", current.description);}
    }

    if (current.name[0] != '\0' && index >= pkg_count) { packages[index++] = current; }

    fclose(fp);
    return 0;
}

int load_repo_package_list(Repo *repo) {
    if (!repo) return -1;
   
    char* home = getenv("HOME");
    if (!home) {perror("unable to get home env"); return -1;}
    char cache_path[4096];
    snprintf(cache_path, sizeof(cache_path), "%s/.local/gralona/cache/%s", home, repo->name);
    if (mkdir_p(cache_path) !=0) { perror("cache directory init failed"); return 1; }
    
    char pkg_list_name[] = "/Packages.gz";
    snprintf(repo->pkg_file_list, sizeof(repo->pkg_file_list), "%s%s" , cache_path, pkg_list_name);
    
    return 0;
}


int load_repo_packages(Repo *repo ) {
    if (!repo) return -1;
    
    if (load_repo_package_list(repo) != 0) return -1;

    repo->pkg_count = count_packages(repo->pkg_file_list);
    if (repo->pkg_count == 0) {
        fprintf(stderr, "No packages found or failed to count\n");
        return -1;
    }

    repo->packages = malloc(sizeof(Package) * repo->pkg_count);
    if (!repo->packages) {
        perror("malloc");
        return -1;
    }

    if (parse_packages(repo->pkg_file_list, repo->packages, repo->pkg_count) != 0) {
        fprintf(stderr, "Failed to parse packages\n");
        free(repo->packages);
        repo->packages = NULL;
        repo->pkg_count = 0;
        return -1;
    }

    return 0;
}
