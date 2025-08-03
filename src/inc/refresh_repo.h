#ifndef REFRESH_REPO_H
#define REFRESH_REPO_H

#define CACHE_DIR_FORMAT "%s/.local/gralona/cache/%s"

static size_t write_data(void* ptr, size_t size, size_t nmemb, FILE* stream);
int refresh_repo (const Repo* repo);

#endif
