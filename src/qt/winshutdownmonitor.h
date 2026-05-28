// Copyright (c) 2019-present The Bitcoin Core developers
// Copyright (c) 2026-present The Sixbit Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://opensource.org/license/mit/.

#ifndef SIXBIT_QT_WINSHUTDOWNMONITOR_H
#define SIXBIT_QT_WINSHUTDOWNMONITOR_H

#ifdef WIN32
#include <QByteArray>
#include <QString>
#include <functional>

#include <windows.h>

#include <QAbstractNativeEventFilter>

class WinShutdownMonitor : public QAbstractNativeEventFilter
{
public:
    WinShutdownMonitor(std::function<void()> shutdown_fn) : m_shutdown_fn{std::move(shutdown_fn)} {}

    /** Implements QAbstractNativeEventFilter interface for processing Windows messages */
    bool nativeEventFilter(const QByteArray &eventType, void *pMessage, qintptr *pnResult) override;

    /** Register the reason for blocking shutdown on Windows to allow clean client exit */
    static void registerShutdownBlockReason(const QString& strReason, const HWND& mainWinId);

private:
    std::function<void()> m_shutdown_fn;
};
#endif

#endif // SIXBIT_QT_WINSHUTDOWNMONITOR_H
