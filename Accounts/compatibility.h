/* vi: set et sw=4 ts=4 cino=t0,(0: */
/*
 * This file is part of libaccounts-qt
 *
 * Copyright (C) 2025 Adriaan de Groot <groot@kde.org>
 *
 * Contact: Alberto Mardegan <alberto.mardegan@canonical.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 */

#ifndef ACCOUNTS_COMPATIBILITY_H
#define ACCOUNTS_COMPATIBILITY_H

/**
 * @file
 *
 * This file definex compatibility-wrappers for Qt 5 and Qt 6 so that
 * callers can call the Qt 6.10 API (approximately) even in Qt 5 or
 * Qt 6 before 6.5.
 */

#include <QByteArray>
#include <QDomDocument>
#include <QString>

namespace compatibility {

// See https://doc.qt.io/qt-6/qdomdocument-parseresult.html
//
// Before Qt 6.5, define a struct with the fields that would-have-been-passed
// as pointers in the call to setContent().

#if QT_VERSION < 0x060500

struct ParseResult {
    operator bool() const { return success; }
    QString errorMessage;
    int errorLine = -1;
    int errorColumn = -1;
    bool success = false;
};

enum ParseOption {
    None = 0,
    UseNamespaceProcessing
};

inline ParseResult setContent(QDomDocument & document, const QByteArray & data, ParseOption option) {
    ParseResult result;
    result.success = document.setContent(data, option == ParseOption::UseNamespaceProcessing, &result.errorMessage, &result.errorLine, &result.errorColumn);
    return result;
}

#else

using ParseResult = QDomDocument::ParseResult;
using ParseOption = QDomDocument::ParseOption;

inline ParseResult setContent(QDomDocument & document, const QByteArray & data, ParseOption option) {
    return document.setContent(data, option);
}

#endif

} // namespace

#endif
