// Copyright (c) 2019-present The Bitcoin Core developers
// Copyright (c) 2021-Copyright (c) 2026-present The Sixbit Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://opensource.org/license/mit/.

#include <qt/transactionoverviewwidget.h>

#include <qt/transactiontablemodel.h>

#include <QListView>
#include <QSize>
#include <QSizePolicy>

TransactionOverviewWidget::TransactionOverviewWidget(QWidget* parent)
    : QListView(parent) {}

QSize TransactionOverviewWidget::sizeHint() const
{
    return {sizeHintForColumn(TransactionTableModel::ToAddress), QListView::sizeHint().height()};
}

void TransactionOverviewWidget::showEvent(QShowEvent* event)
{
    Q_UNUSED(event);
    QSizePolicy sp = sizePolicy();
    sp.setHorizontalPolicy(QSizePolicy::Minimum);
    setSizePolicy(sp);
}
