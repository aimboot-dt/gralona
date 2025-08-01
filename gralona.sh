#/bin/bash

# Set repo and cache dir
REPO_URL="http://packages.linuxmint.com/dists/elsie/main/binary-amd64/Packages.gz"
CACHE_DIR="./cache"
PKG_NAME="$1"

mkdir -p "$CACHE_DIR"

echo "[+] Downloading package index..."
wget -qO "$CACHE_DIR/Packages.gz" "$REPO_URL"

echo "[+] Searching for '$PKG_NAME'..."
zgrep -A 10 "^Package: $PKG_NAME$" "$CACHE_DIR/Packages.gz" > "$CACHE_DIR/found.txt"

FILENAME=$(grep "^Filename: " "$CACHE_DIR/found.txt" | awk '{print $2}')
if [[ -z "$FILENAME" ]]; then
    echo "[-] Package not found."
    exit 1
fi

DEB_URL="http://packages.linuxmint.com/$FILENAME"
DEB_FILE="/tmp/$(basename "$FILENAME")"

echo "[+] Downloading $DEB_URL..."
wget -qO "$DEB_FILE" "$DEB_URL"

echo "[+] Installing package..."
sudo dpkg -i "$DEB_FILE"

echo "[+] Cleaning up..."
rm "$DEB_FILE"

