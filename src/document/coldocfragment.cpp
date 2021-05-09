/*
Collett – Collett Document Fragment Class
=========================================

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

#include "coldocfragment.h"

#include <QString>

#include <QDebug>

namespace Collett {

ColDocFragment::ColDocFragment(const QString &text) {

    if (!text.startsWith("{f")) {
        fValid = false;
        return;
    }

    qsizetype endFmt = text.indexOf('}');
    if (endFmt < 0) {
        fValid = false;
        return;
    }

    fText = text.sliced(endFmt+1);

    for (int i=1; i<endFmt; ++i) {
        if (text.at(i) == 'b') {
            fBold = true;
            continue;
        }
        if (text.at(i) == 'i') {
            fItalic = true;
            continue;
        }
        if (text.at(i) == 'u') {
            fUnderline = true;
            continue;
        }
        if (text.at(i) == 's') {
            fStrikeOut = true;
            continue;
        }
    }

    fValid = true;
}

} // namespace Collett
