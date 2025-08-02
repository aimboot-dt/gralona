#include "repos.h"
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "refresh_cache_all.h"
#include "refresh_repo.h"

void refresh_cache_all() {
    load_repos();
    for(int r = 0; r < repo_count; ++r){
	refresh_repo(&repos[r]);
    }
}

