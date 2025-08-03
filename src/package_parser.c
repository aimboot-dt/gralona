#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "package_parser.h"

#define MAX_LINE 1024

PackageNode *parse_packages_file(const char *filepath) {
    FILE *fp = fopen(filepath, "r");
    if (!fp) return NULL;

    char line[MAX_LINE];
    Package current = {0};
    PackageNode *head = NULL;
    PackageNode *tail = NULL;

    while (fgets(line, sizeof(line), fp)) {
        if (strcmp(line, "\n") == 0 || strcmp(line, "\r\n") == 0) {
            if (current.name[0] != '\0') {
                PackageNode *new_node = malloc(sizeof(PackageNode));
                if (!new_node) break;
                new_node->pkg = current;
                new_node->next = NULL;
                if (!head) head = new_node;
                else tail->next = new_node;
                tail = new_node;
                memset(&current, 0, sizeof(Package));
            }
            continue;
        }

        if (strncmp(line, "Package:", 8) == 0) sscanf(line + 8, "%255s", current.name);
	if (strncmp(line, "Version:", 8) == 0) sscanf(line + 8, "%63s", current.version);
	if (strncmp(line, "Filename:", 9) == 0) sscanf(line + 9, "%511s", current.filename);
	if (strncmp(line, "Description:", 12) == 0) sscanf(line + 12, "%s", current.description);
        // Add more fields as needed
    }

    if (current.name[0] != '\0') {
        PackageNode *new_node = malloc(sizeof(PackageNode));
        new_node->pkg = current;
        new_node->next = NULL;
        if (!head) head = new_node;
        else tail->next = new_node;
        tail = new_node;
    }

    fclose(fp);
    return head;
}	
