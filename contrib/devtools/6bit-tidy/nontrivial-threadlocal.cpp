// Copyright (c) 2019-present The Bitcoin Core developers
// Copyright (c) 2026-present The Sixbit Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://opensource.org/license/mit/

#include "nontrivial-threadlocal.h"

#include <clang/ASTMatchers/ASTMatchFinder.h>

// Matcher adapted from clang-tidy's UnusedRaiiCheck.
namespace {
AST_MATCHER(clang::CXXRecordDecl, hasNonTrivialDestructor) {
    // TODO: If the destructor exists but is empty, we may want to avoid warning.
    return Node.hasDefinition() && Node.hasNonTrivialDestructor();
}
} // namespace

namespace SixBit {

void NonTrivialThreadLocal::registerMatchers(clang::ast_matchers::MatchFinder* finder)
{
    using namespace clang::ast_matchers;

    finder->addMatcher(
        varDecl(
            hasThreadStorageDuration(),
            hasType(
                hasCanonicalType(
                    anyOf(
                        recordType(hasDeclaration(cxxRecordDecl(hasNonTrivialDestructor()))),
                        arrayType(hasElementType(
                            hasCanonicalType(
                                recordType(hasDeclaration(cxxRecordDecl(hasNonTrivialDestructor())))
                            )
                        ))
                    )
                )
            )
        ).bind("nontrivial_threadlocal"),
        this);
}

void NonTrivialThreadLocal::check(const clang::ast_matchers::MatchFinder::MatchResult& Result)
{
    if (const clang::VarDecl* var =
            Result.Nodes.getNodeAs<clang::VarDecl>("nontrivial_threadlocal")) {
        diag(var->getBeginLoc(),
             "thread_local variable has a non-trivial destructor");
    }
}

} // namespace SixBit
