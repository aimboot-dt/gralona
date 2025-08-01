#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "package_parser.h"

#define MAX_LINE 1024

Package *parse_packages_file(const char *filepath, int *count) {
    FILE *fp = fopen(filepath, "r");
    if (!fp) return NULL;

    char line[MAX_LINE];
    int capacity = 32;
    int index = 0;
    Package *packages = malloc(capacity * sizeof(Package));
    Package current = {0};

    while (fgets(line, sizeof(line), fp)) {
        if (strcmp(line, "\n") == 0 || strcmp(line, "\r\n") == 0) {
            if (current.name[0] != '\0') {
                if (index >= capacity) {
                    capacity *= 2;
                    packages = realloc(packages, capacity * sizeof(Package));
                }
                packages[index++] = current;
                memset(&current, 0, sizeof(Package));
            }
            continue;
        }

        if (strncmp(line, "Package:", 8) == 0) {
            sscanf(line + 8, "%s", current.name);
        } else if (strncmp(line, "Version:", 8) == 0) {
            sscanf(line + 8, "%s", current.version);
        } else if (strncmp(line, "Filename:", 9) == 0) {
            sscanf(line + 9, "%s", current.filename);
        }
    }

    if (current.name[0] != '\0') {
        if (index >= capacity) {
            capacity++;
            packages = realloc(packages, capacity * sizeof(Package));
        }
        packages[index++] = current;
    }

    fclose(fp);
    *count = index;
    return packages;
}

