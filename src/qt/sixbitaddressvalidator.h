// Copyright (c) 2011-2020 The Sixbit Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://opensource.org/license/mit/.

#ifndef SIXBIT_QT_6BITADDRESSVALIDATOR_H
#define SIXBIT_QT_6BITADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class SixbitAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit SixbitAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

/** sixbit address widget validator, checks for a valid sixbit address.
 */
class SixbitAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit SixbitAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

#endif // SIXBIT_QT_6BITADDRESSVALIDATOR_H
