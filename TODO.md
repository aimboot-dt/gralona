P1: 
Setup gralona to work with different repos (COMPLETE)
Test gralona (COMPLETE)
P2:
Add CLI options (-s for search, -i for install, -u for upgrade, -r for remove) (COMPLETE)
Migrate to C
Setup Deps resolution system (maybe custom, maybe apt -f install)
Cache metadata for quicker searching (COMPLETE)
Create autoconfig via bash to autoconfigure which repos to source
P3:
Let gralona have multiple repos to search in
    Organize cache for multiple repo usage (maybe have a tree-like structure)
        something like 
        debian
            stable
                main
                non-free
                ...
            testing
                main
                non-free
                ...
        ubuntu
            ...
        mint
            ...
    Allow gralona to select which distro's repo to access
    Give it something to detect when two repos might intersect (different versions of the same package, conflicting dependencies, etc)

P4: will cross that bridge when we get there
