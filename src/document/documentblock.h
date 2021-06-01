/*
Collett – Collett Document Block Class
======================================

This file is a part of Collett
Copyright 2020–2021, Veronica Berglyd Olsen

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef COL_DOCUMENTBLOCK_H
#define COL_DOCUMENTBLOCK_H

#include <QList>
#include <QString>
#include <QTextBlock>

namespace Collett {

class DocumentBlock
{

public:
    struct Fragment {
        bool plain     = false;
        bool valid     = false;
        bool bold      = false;
        bool italic    = false;
        bool underline = false;
        bool strikeout = false;
        QString text   = "";
    };

    struct Styles {
        bool          valid     = false;
        int           header    = 0;
        Qt::Alignment alignemnt = Qt::AlignLeft;
        bool          indent    = false;
    };

    struct Block {
        bool            valid = false;
        Styles          styles;
        QList<Fragment> fragments;
        QString         text;
    };

    static QString encodeQTextBlock(const QTextBlock &qBlock);
    static Block decodeText(const QString &text);

private:
    DocumentBlock() {};
    ~DocumentBlock() {};

    static Styles parseBlockFormat(const QString &format);
    static Fragment parseFragment(const QString &text);

};
} // namespace Collett

#endif // COL_DOCUMENTBLOCK_H
