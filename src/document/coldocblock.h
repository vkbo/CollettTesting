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

#ifndef COLDOCBLOCK_H
#define COLDOCBLOCK_H

#include <QString>
#include <QList>
#include <QTextBlock>

namespace Collett {

class ColDocBlock
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

    struct Block {
        int           header    = 0;
        Qt::Alignment alignemnt = Qt::AlignLeft;
        bool          indent    = false;
    };

    ColDocBlock();
    ~ColDocBlock() {};

    static QString encodeQTextBlock(const QTextBlock &qBlock);
    void unpackText(const QString &text);

    bool isValid() {
        return blockValid;
    }

    Block blockStyle() {
        return blockStyles;
    }

    QList<Fragment> fragments() {
        return blockFragments;
    }

private:
    bool            blockValid;
    Block           blockStyles;
    QList<Fragment> blockFragments;

    Block    parseBlockFormat(const QString &format);
    Fragment parseFragment(const QString &text);

};
} // namespace Collett

#endif // COLDOCBLOCK_H
