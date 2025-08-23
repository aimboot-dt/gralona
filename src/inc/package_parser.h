// package_parser.h
#ifndef PACKAGE_PARSER_H
#define PACKAGE_PARSER_H

#define MAX_NAME 256
#define MAX_VERSION 64
#define MAX_FILENAME 512
#define MAX_DESCRIPTION 1024
#define MAX_DEPENDS 32

typedef struct {
    char name[MAX_NAME];
    char version[MAX_VERSION];
    char filename[MAX_FILENAME];
    char description[MAX_DESCRIPTION];
    char *depends[MAX_DEPENDS];
    int depends_count;
} Package;

void display_package(Package* package);


#endif // PACKAGE_PARSER_H
