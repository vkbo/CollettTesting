/*
Collett – Main Settings Class
=============================

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

#ifndef COLLETTSETTINGS_H
#define COLLETTSETTINGS_H

// Settings
#define CNF_WIN_SIZE   "GuiMain/winSize"
#define CNF_TREE_WIDTH "GuiMain/treeSplit"
#define CNF_EDIT_WIDTH "GuiMain/editorSplit"

#include "collett.h"

namespace Collett {

class CollettSettings
{

public:
    CollettSettings() {};
    ~CollettSettings() {};

private:

};
} // namespace Collett

#endif // COLLETTSETTINGS_H
