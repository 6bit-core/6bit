// Copyright (c) 2019-present The Bitcoin Core developers
// Copyright (c) 2011-Copyright (c) 2026-present The Sixbit Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://opensource.org/license/mit/.

#include <qt/qvaluecombobox.h>

QValueComboBox::QValueComboBox(QWidget* parent)
    : QComboBox(parent)
{
    connect(this, qOverload<int>(&QComboBox::currentIndexChanged), this, &QValueComboBox::handleSelectionChanged);
}

QVariant QValueComboBox::value() const
{
    return itemData(currentIndex(), role);
}

void QValueComboBox::setValue(const QVariant &value)
{
    setCurrentIndex(findData(value, role));
}

void QValueComboBox::setRole(int _role)
{
    this->role = _role;
}

void QValueComboBox::handleSelectionChanged(int idx)
{
    Q_EMIT valueChanged();
}
