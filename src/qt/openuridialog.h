// Copyright (c) 2019-present The Bitcoin Core developers
// Copyright (c) 2026-present The Sixbit Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://opensource.org/license/mit/.

#ifndef SIXBIT_QT_OPENURIDIALOG_H
#define SIXBIT_QT_OPENURIDIALOG_H

#include <QDialog>

class PlatformStyle;

namespace Ui {
    class OpenURIDialog;
}

class OpenURIDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OpenURIDialog(const PlatformStyle* platformStyle, QWidget* parent);
    ~OpenURIDialog();

    QString getURI();

public Q_SLOTS:
    void accept() override;

protected:
    void changeEvent(QEvent* e) override;

private:
    Ui::OpenURIDialog* ui;
    const PlatformStyle* m_platform_style;
};

#endif // SIXBIT_QT_OPENURIDIALOG_H
