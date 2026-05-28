// Copyright (c) 2019-present The Bitcoin Core developers
// Copyright (c) 2026-present The Sixbit Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://opensource.org/license/mit/.

#ifndef SIXBIT_QT_TEST_OPTIONTESTS_H
#define SIXBIT_QT_TEST_OPTIONTESTS_H

#include <common/settings.h>
#include <qt/optionsmodel.h>
#include <univalue.h>

#include <QObject>

class OptionTests : public QObject
{
    Q_OBJECT
public:
    explicit OptionTests(interfaces::Node& node);

private Q_SLOTS:
    void init(); // called before each test function execution.
    void migrateSettings();
    void integerGetArgBug();
    void parametersInteraction();
    void extractFilter();

private:
    interfaces::Node& m_node;
    common::Settings m_previous_settings;
};

#endif // SIXBIT_QT_TEST_OPTIONTESTS_H
