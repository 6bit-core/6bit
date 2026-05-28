// Copyright (c) 2019-present The Bitcoin Core developers
// Copyright (c) 2026-present The Sixbit Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://opensource.org/license/mit/

#ifndef NONTRIVIAL_THREADLOCAL_H
#define NONTRIVIAL_THREADLOCAL_H

#include <clang-tidy/ClangTidyCheck.h>

namespace SixBit {

// Warn about any thread_local variable with a non-trivial destructor.
class NonTrivialThreadLocal final : public clang::tidy::ClangTidyCheck
{
public:
    NonTrivialThreadLocal(clang::StringRef Name, clang::tidy::ClangTidyContext* Context)
        : clang::tidy::ClangTidyCheck(Name, Context) {}

    bool isLanguageVersionSupported(const clang::LangOptions& LangOpts) const override
    {
        return LangOpts.CPlusPlus;
    }

    void registerMatchers(clang::ast_matchers::MatchFinder* Finder) override;
    void check(const clang::ast_matchers::MatchFinder::MatchResult& Result) override;
};

} // namespace SixBit

#endif // NONTRIVIAL_THREADLOCAL_H
