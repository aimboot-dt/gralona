#include <stdio.h>
#include <unistd.h>
#include "repos.h"
#include "refresh_cache_all.h"
#include "refresh_repo.h"
#include "package_parser.h"

/* #include "refresh_cache.h"
*/
#include "search_for_pkg.h"
/* #include "install_pkg.h"
#include "remove_pkg.h"
#include "refresh_pkg.h"
#include "update_pkg.h"
#include "update_all_pkg.h"
*/

//void install()        { puts("Installing package..."); }
//void search()         { puts("Searching remote..."); }
void delete_pkg()     { puts("Deleting package..."); }
void refresh_pkg()    { puts("Refreshing package..."); }
void update_pkg()     { puts("Updating package..."); }
void update_all()     { puts("Updating all packages..."); }
//void refresh_cache()  { puts("Refreshing cache..."); }

int main(int argc, char *argv[]) {
    int opt;
    int current_repo_idx = 0;
    load_repos();
   while ((opt = getopt(argc, argv, "i:s:d:u:r:UR")) != -1) {
        switch (opt) {
            case 'r': 
                if(search_for_repo(optarg) > 0) {current_repo_idx = search_for_repo(optarg);} 
                printf("in repo %s\n", repos[current_repo_idx].name);
                if(load_repo_packages(&repos[current_repo_idx]) != 0) {
                    fprintf(stderr, "Loading repos failed");
                } break;
            case 'i': if (install_package_from_repo(&repos[current_repo_idx], 
                          search_package_in_repo(&repos[current_repo_idx], optarg)) != 0) {
                fprintf(stderr, "error installing package"); break;}
            case 's': display_package(search_package_in_repo(&repos[current_repo_idx], optarg)); break;
            case 'd': delete_pkg(); break;
            case 'u': update_pkg(); break;
            case 'U': update_all(); break;
            case 'R': refresh_cache_all(); break;
            default:
                fprintf(stderr, "Usage: %s [-isdurUR]\n", argv[0]);
                return 1;
        }
    }
    return 0;
}

