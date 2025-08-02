#ifndef REFRESH_REPO_H
#define REFRESH_REPO_H

#define CACHE_DIR_FORMAT "%s/.local/gralona/cache/%s"

static size_t write_data(void*, size_t, size_t, FILE*);
int refresh_repo (const Repo* repo);

#endif
