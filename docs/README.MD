# Gralona

**Gralona** is a lightweight, DIY package installer (inspired by apt/Aptitude) that:

- ✅ Searches a remote Debian-style(though not limited to debian) repository index (`Packages.gz`)
- ✅ Downloads `.deb` packages
- ✅ Installs them via `dpkg -i`
- ✅ Cleans up afterward

---

## 🚀 Quick Start

1. Clone the repo:

   ```bash
   git clone https://github.com/aimboot-dt/gralona.git
   cd gralona

2. Make the script executable
    ```bash
    chmod +x gralona.sh

3. Install packages by name
    ```bash
    ./gralona.sh <package-name> #e.g. ./gralona.sh mint-themes

---

🧾 How It Works

- Downloads the Packages.gz index from a configured repository

- Uses zgrep to find metadata for the specified package

- Builds the .deb download URL

- Downloads + runs dpkg -i

- Deletes the downloaded .deb after install

You can customize the repository URL in gralona.sh.

---

📂 Project Structure

	gralona/
	├── gralona.sh         # Main shell script
	├── repo.list          # Configuration for your repo(s)
	├── cache/             # Caches downloaded metadata
	├── docs/              # Optional docs or how‑tos
	└── TODO.md            # Roadmap & feature ideas

---

🔧 Features & Roadmap
	
	Feature | Status
	:--- | ---:
	Package search|✅ Built-in
	.deb download | ✅ ✅ 
	Installation |	✅ dpkg -i 
	Auto-fix deps |🔨 Future 
	Version aware |🔨 Future 
	Repository caching 🔨 Future 
	Cleaner CLI flags| 🔨 Future 

---

🔄 Contribution

Go ahead 👍 If you're into:

 Parsing Packages.gz metadata

 Evaluating dependencies

 Improving CLI usability

 Porting to C / Rust / Python

you're totally welcome. Fork it, code it, send PRs, all help is welcome,

---

⚖️ License

Distributed under the MIT License. See LICENSE.

---

🛠️ Objective

This is not a full replacement for APT. Gralona is meant to be:

    Educational: learn how package managers play with control files, dependency logic, and indexes.

    Minimal: a portable, self-contained installer script.

    Expandable: lay groundwork to build more advanced features later.

    Cross Base (?): able to download packages from other Distro types (rpm, pacman, etc) (if that's even possible)


Enjoy Gralona — your custom Debian package installer. If you get stuck, hit me up.

