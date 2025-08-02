#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "repos.h"
#include "refresh_repo.h" 

static size_t write_data(void* ptr, size_t size, size_t nmemb, FILE* stream) { return fwrite(ptr, size, nmemb, stream); }

int refresh_repo(const Repo* repo) {
    CURL* curl;
    CURLcode res;

    char* home = getenv("HOME");
    if (!home) {
        fprintf(stderr, "Could not get $HOME\n");
        return 1;
    }

    char cache_path[PATH_MAX];
    snprintf(cache_path, sizeof(cache_path), "%s/.local/gralona/cache/%s", home, repo->name);

    FILE* fp = fopen(cache_path, "wb");
    if (!fp) {
        perror("Failed to open cache file");
        return 1;
    }

    curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Failed to init curl\n");
        fclose(fp);
        return 1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, repo->url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);

    printf("Refreshing: %s\n", repo->name);
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "Failed to refresh %s: %s\n", repo->name, curl_easy_strerror(res));
    } else {
        printf("✓ Refreshed: %s\n", repo->name);
    }

    curl_easy_cleanup(curl);
    fclose(fp);

    return res != CURLE_OK;
}

