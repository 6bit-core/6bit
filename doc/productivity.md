# Productivity Notes

## General

### Cache compilations with `ccache`

ccache speeds up recompilation by caching previous builds.

Install via your package manager and run:
cmake -B build

Example config (~/.ccache/ccache.conf):
max_size = 50.0G
base_dir = /home/yourname

Do NOT set base_dir to /.

---

### Disable features

cmake -B build -LH

---

### Use all CPU threads

cmake --build build -j "$(($(nproc)+1))"

---

### Only build what you need

cmake --build build --target sixbitd sixbit-cli

---

### Compile on multiple machines

Use distcc: https://www.distcc.org

---

### Git worktrees

git worktree add -b my-branch ../new-dir base-commit

---

### Dummy rebases

git rebase -i --autosquash "$(git merge-base master HEAD)"

---

## Writing code

clang-format-diff.py
yapf-diff.py

---

## Rebasing / Merging

git config merge.conflictstyle diff3

---

## Reviewing code

git diff -w
git diff --word-diff
git diff --patience

---

## Fetch commits

git fetch origin <commit-hash>

---

## PR refs

[remote "upstream-pull"]
    fetch = +refs/pull/*/head:refs/remotes/upstream-pull/*
    url = git@github.com:6bit-core/6bit.git

---

## Fetch PRs

git fetch upstream pull/<number>/head

---

## Aliases

[alias]
pr = "!f() { git fetch upstream pull/$1/head:pr-$1 && git switch pr-$1; }; f"
pru = "!f() { git fetch --update-head-ok -f upstream pull/$1/head:pr-$1; }; f"

---

## Range diff

git range-diff master old-head new-head
