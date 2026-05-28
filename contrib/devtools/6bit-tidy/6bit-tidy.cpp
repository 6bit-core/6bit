// Copyright (c) 2019-present The Bitcoin Core developers
// Copyright (c) 2026-present The Sixbit Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://opensource.org/license/mit/

#include "nontrivial-threadlocal.h"

#include <clang-tidy/ClangTidyModule.h>
#include <clang-tidy/ClangTidyModuleRegistry.h>

class SixBitModule final : public clang::tidy::ClangTidyModule
{
public:
    void addCheckFactories(clang::tidy::ClangTidyCheckFactories& CheckFactories) override
    {
        CheckFactories.registerCheck<SixBit::NonTrivialThreadLocal>("sixbit-nontrivial-threadlocal");
    }
};

static clang::tidy::ClangTidyModuleRegistry::Add<SixBitModule>
    X("sixbit-module", "Adds sixbit checks.");

volatile int SixBitModuleAnchorSource = 0;
