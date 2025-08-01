#/bin/bash

# Set repo and cache dir
REPO_URL="http://packages.linuxmint.com/dists/elsie/main/binary-amd64/Packages.gz"
CACHE_DIR="./cache"
PKG_INDEX="$CACHE_DIR/Packages.gz"
mkdir -p "$CACHE_DIR"

# --- Helper Functions ---

refresh_cache() {
    echo "[+] Refreshing package index..."
    wget -qO "$PKG_INDEX" "$REPO_URL" || { echo "[-] Failed to update cache."; exit 1; }
    echo "[+] Cache updated."
}

search_pkg() {
    local name="$1"
    if [[ ! -f "$PKG_INDEX" ]]; then
        echo "[-] Cache missing. Run with -R to fetch index."
        exit 1
    fi
    zgrep -A 10 "^Package: $name$" "$PKG_INDEX"
}

install_pkg() {
    local name="$1"
    echo "[+] Searching for '$name'..."
    zgrep -A 10 "^Package: $name$" "$PKG_INDEX" > "$CACHE_DIR/found.txt"

    FILENAME=$(grep "^Filename: " "$CACHE_DIR/found.txt" | awk '{print $2}')
    if [[ -z "$FILENAME" ]]; then
        echo "[-] Package not found."
        exit 1
    fi

    DEB_URL="http://packages.linuxmint.com/$FILENAME"
    DEB_FILE="/tmp/$(basename "$FILENAME")"

    echo "[+] Downloading $DEB_URL..."
    wget -qO "$DEB_FILE" "$DEB_URL" || { echo "[-] Failed to download."; exit 1; }

    echo "[+] Installing package..."
    sudo dpkg -i "$DEB_FILE"
    rm "$DEB_FILE"
}

# --- Seen CLI Side ---

usage() {
    echo "Usage: $0 [-i package] [-s package] [-d package] [-r package] [-R]"
    exit 1
}



if [[ $# -eq 0 ]]; then
    usage
fi

while getopts ":i:s:u:r:R" opt; do
    case $opt in
        i) install_pkg "$OPTARG" ;;
        s) search_pkg "$OPTARG" ;;
        u) echo "Upgrade not implemented yet." ;;
        r) echo "Remove not implemented yet." ;;
        R) refresh_cache ;;
        \?) echo "[-] Invalid option: -$OPTARG" >&2; usage ;;
        :) echo "[-] Option -$OPTARG requires an argument." >&2; usage ;;
    esac
done

