// Copyright (c) 2019-present The Bitcoin Core developers
// Copyright (c) 2011-Copyright (c) 2026-present The Sixbit Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://opensource.org/license/mit/.

#include <qt/openuridialog.h>
#include <qt/forms/ui_openuridialog.h>

#include <qt/guiutil.h>
#include <qt/platformstyle.h>
#include <qt/sendcoinsrecipient.h>

#include <QAbstractButton>
#include <QLineEdit>
#include <QUrl>

OpenURIDialog::OpenURIDialog(const PlatformStyle* platformStyle, QWidget* parent) : QDialog(parent, GUIUtil::dialog_flags),
                                                                                    ui(new Ui::OpenURIDialog),
                                                                                    m_platform_style(platformStyle)
{
    ui->setupUi(this);
    ui->pasteButton->setIcon(m_platform_style->SingleColorIcon(":/icons/editpaste"));
    QObject::connect(ui->pasteButton, &QAbstractButton::clicked, ui->uriEdit, &QLineEdit::paste);

    GUIUtil::handleCloseWindowShortcut(this);
}

OpenURIDialog::~OpenURIDialog()
{
    delete ui;
}

QString OpenURIDialog::getURI()
{
    return ui->uriEdit->text();
}

void OpenURIDialog::accept()
{
    SendCoinsRecipient rcp;
    if (GUIUtil::parsesixbitURI(getURI(), &rcp)) {
        /* Only accept value URIs */
        QDialog::accept();
    } else {
        ui->uriEdit->setValid(false);
    }
}

void OpenURIDialog::changeEvent(QEvent* e)
{
    if (e->type() == QEvent::PaletteChange) {
        ui->pasteButton->setIcon(m_platform_style->SingleColorIcon(":/icons/editpaste"));
    }

    QDialog::changeEvent(e);
}
