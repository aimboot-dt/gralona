#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include "repos.h"
#include "refresh_repo.h" 
#include "mkdir_p.h"
#include "zlib.h"

static size_t write_data(void* ptr, size_t size, size_t nmemb, FILE* stream) { return fwrite(ptr, size, nmemb, stream); }


int decompress_gz(const char *src, const char *dst) {
    gzFile gzfp = gzopen(src, "rb");
    if (!gzfp) {
        perror("gzopen failed");
        return -1;
    }

    FILE *outfp = fopen(dst, "wb");
    if (!outfp) {
        perror("fopen failed");
        gzclose(gzfp);
        return -1;
    }

    char buffer[8192];
    int bytes;
    while ((bytes = gzread(gzfp, buffer, sizeof(buffer))) > 0) {
        fwrite(buffer, 1, bytes, outfp);
    }

    gzclose(gzfp);
    fclose(outfp);
    return 0;
}

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
    if (mkdir_p(cache_path) !=0) { perror("cache directory init failed"); return 1; }
    /* bad code 
    char make_cache_dir[PATH_MAX];
    snprintf (make_cache_dir, sizeof(make_cache_dir), “mkdir -p %s”, cache_path)
    system(make_cache_dir);
    */
    if(mkdir(cache_path, 0755) == -1 && errno != EEXIST) { perror("mkdir failed"); return 1; }
    
    char cache_file[PATH_MAX+13];
    char pkg_list_name[] = "/Packages.gz";
    snprintf(cache_file, sizeof(cache_file), "%s%s" , cache_path, pkg_list_name);
    
    FILE* fp = fopen(cache_file, "wb");
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

    char decompressed_file[PATH_MAX+12];
    snprintf(decompressed_file, sizeof(decompressed_file), "%s/Packages", cache_path);

    if (decompress_gz(cache_file, decompressed_file) != 0) {
        fprintf(stderr, "Failed to decompress %s\n", cache_file);
        return 1;
}
    return res != CURLE_OK;
}

