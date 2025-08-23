#ifndef SEARCH_FOR_PKG_H
#define SEARCH_FOR_PKG_H

#include "package_parser.h"
#include "repos.h"

Package *search_package_in_repo (Repo *repo, const char *name);
int install_package_from_repo (Repo *repo, Package* pkg_to_install);
#endif
