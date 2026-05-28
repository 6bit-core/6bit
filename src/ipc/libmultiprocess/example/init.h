// Copyright (c) The Sixbit Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://opensource.org/license/mit/.

#ifndef EXAMPLE_INIT_H
#define EXAMPLE_INIT_H

#include <calculator.h>
#include <memory>
#include <printer.h>

class Init
{
public:
    virtual ~Init() = default;
    virtual std::unique_ptr<Printer> makePrinter() { return nullptr; }
    virtual std::unique_ptr<Calculator> makeCalculator(std::unique_ptr<Printer> printer) { return nullptr; }
};

#endif // EXAMPLE_INIT_H
