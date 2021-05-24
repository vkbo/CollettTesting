/*
Collett – Core Data Class
=========================

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

#include "data.h"
#include "project.h"

#include <QWidget>
#include <QDir>

namespace Collett {

bool ColData::openProject(const QDir path) {

    m_project = new ColProject(path);
    bool status = m_project->openProject();
    m_hasProject = m_project->hasProject();

    return status;
}

bool ColData::saveProject() {
    if (m_hasProject) {
        return m_project->saveProject();
    } else {
        return false;
    }
}

ColProject* ColData::getProject() {
    if (m_hasProject) {
        return m_project;
    } else {
        return nullptr;
    }
}

} // namespace Collett
