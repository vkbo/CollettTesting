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

namespace Collett {

class ColDocBlock
{

public:

    struct Fragment {
        bool valid     = false;
        bool bold      = false;
        bool italic    = false;
        bool underline = false;
        bool strikeout = false;
        QString text   = "";
    };

    ColDocBlock();
    ~ColDocBlock() {};

    void unpackText(const QString &text);
    QString packText();

    void setBlockType(int blockType);
    void setBlockAlignment(Qt::Alignment alignFlag);

    bool isValid() {
        return blockValid;
    }

    QList<Fragment> fragments() {
        return blockFragments;
    }

private:
    QList<Fragment> blockFragments;

    bool          blockValid;
    int           blockTypeValue;
    Qt::Alignment blockAlignValue;

    Fragment parseFragment(const QString &text);

};
} // namespace Collett

#endif // COLDOCBLOCK_H
