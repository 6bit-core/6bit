# Sixbit Core

<p align="center">
  <img src="https://6bit.dev/logo.png" width="120" />
</p>

<p align="center">
  <a href="https://github.com/sixbit-core/sixbit/actions">
    <img src="https://img.shields.io/github/actions/workflow/status/sixbit-core/sixbit/ci.yml?branch=master" alt="CI Status">
  </a>
  <a href="https://github.com/sixbit-core/sixbit/blob/master/LICENSE">
    <img src="https://img.shields.io/github/license/sixbit-core/sixbit" alt="License">
  </a>
  <a href="https://github.com/sixbit-core/sixbit/issues">
    <img src="https://img.shields.io/github/issues/sixbit-core/sixbit" alt="Issues">
  </a>
  <a href="https://github.com/sixbit-core/sixbit/pulls">
    <img src="https://img.shields.io/github/issues-pr/sixbit-core/sixbit" alt="Pull Requests">
  </a>
</p>

---

# Contributing to Sixbit Core

The **Sixbit Core** project follows an open contributor model. Anyone can contribute through:

- Code contributions
- Peer review
- Testing
- Documentation

Website: https://6bit.dev  
Repository: https://github.com/sixbit-core/sixbit  

---

## ?? Getting Started

New contributors are welcome.

Best way to start:
- Review pull requests
- Run tests
- Explore the codebase

Before contributing:
- Build Sixbit Core
- Run unit, functional, and fuzz tests

---

## ?? Repository Structure

- **Main Node Repo** ? https://github.com/sixbit-core/sixbit  
- **GUI Repo** ? https://github.com/sixbit-core/gui  

### Rule of Thumb

| Change Type | Repo |
|------------|------|
| `src/qt` only | GUI repo |
| Core logic / consensus | Node repo |
| Build system / interfaces | Node repo |

---

## ?? Contributor Workflow

1. Fork the repo  
2. Create a branch  
3. Make changes  
4. Commit  
5. Push  
6. Open Pull Request  

---

## ?? Commit Guidelines

- Keep commits **atomic**
- Each commit must build successfully
- Include tests when behavior changes

### Commit Message Format

```
area: short description (=50 chars)

Detailed explanation of WHAT and WHY.
```

Example:
```
net: Improve peer eviction logic

Reduces memory pressure under heavy load.
```

---

## ?? Pull Requests

### Title Format

Prefix with component:

- `consensus`
- `net` / `p2p`
- `wallet`
- `rpc`
- `qt` / `gui`
- `test` / `ci`
- `build`
- `doc`
- `refactor`

Example:
```
wallet: Improve descriptor import performance
```

### PR Description Rules

- Explain **what** and **why**
- Link issues (`fixes #123`)
- NO `@mentions` in description

---

## ?? Testing Requirements

All PRs must:

- Pass existing test suite
- Add tests when fixing bugs
- Avoid regressions

Types:
- Unit tests
- Functional tests
- Fuzz tests

---

## ?? Code Review

Expect:

- Concept feedback
- Code feedback
- Requests for changes

### Review Tags

- `Concept ACK / NACK`
- `Approach ACK / NACK`
- `ACK <commit>`

---

## ?? Rebasing

```
git fetch https://github.com/sixbit-core/sixbit
git rebase FETCH_HEAD
```

---

## ?? Squashing

```
git rebase -i HEAD~n
git push -f
```

---

## ?? Coding Rules

- Follow developer notes
- No mixed refactor + logic changes
- Keep PRs small and focused

---

## ?? Important Rules

- No `@mentions` in commits or PR descriptions
- No large “mega PRs”
- Keep history clean (no merge commits)

---

## ?? Philosophy

Good PRs are:

- Small
- Clear
- Well-tested
- Easy to review

Bad PRs are:

- Too large
- Too complex
- Poorly justified

---

## ?? Consensus Changes

Require:

- BIP proposal
- Extensive discussion
- High review standard

---

## ?? Backporting

Metadata format:

```
Github-Pull: #1234
Rebased-From: <commit>
```

---

## ?? License

By contributing, you agree your work is licensed under the MIT License.

---

## ?? Final Tip

**Best way to get your PR merged:**
?? Review other PRs first

