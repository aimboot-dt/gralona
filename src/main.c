#include <stdio.h>
#include <unistd.h>
#include "repos.h"
#include "refresh.h"
#include "package_parser.h"

/* #include "refresh_cache.h"
#include "search_for_pkg.h"
#include "install_pkg.h"
#include "remove_pkg.h"
#include "refresh_pkg.h"
#include "update_pkg.h"
#include "update_all_pkg.h"
*/

void install()        { puts("Installing package..."); }
void search()         { puts("Searching remote..."); }
void delete_pkg()     { puts("Deleting package..."); }
void refresh_pkg()    { puts("Refreshing package..."); }
void update_pkg()     { puts("Updating package..."); }
void update_all()     { puts("Updating all packages..."); }
//void refresh_cache()  { puts("Refreshing cache..."); }

int main(int argc, char *argv[]) {
    int opt;
    
    load_repos("repos.list");
   while ((opt = getopt(argc, argv, "isdurUR")) != -1) {
        switch (opt) {
	    case 'i': install(); break;
            case 's': search(); break;
            case 'd': delete_pkg(); break;
            case 'r': refresh_pkg(); break;
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

