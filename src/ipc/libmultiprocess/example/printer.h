// Copyright (c) The Sixbit Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://opensource.org/license/mit/.

#ifndef EXAMPLE_PRINTER_H
#define EXAMPLE_PRINTER_H

#include <string>

class Printer
{
public:
    virtual ~Printer() = default;
    virtual void print(const std::string& message) = 0;
};

#endif // EXAMPLE_PRINTER_H
