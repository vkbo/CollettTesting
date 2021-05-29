/*
Collett – Project Model Class
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

#include "storymodel.h"
#include "storytree.h"
#include "storyitem.h"
#include "project.h"

#include <QAbstractListModel>
#include <QModelIndex>
#include <QObject>
#include <QVariant>

namespace Collett {

StoryModel::StoryModel(Project *project, QObject *parent)
    : m_project(project), QAbstractListModel(parent)
{
}

int StoryModel::rowCount(const QModelIndex &parent) const {
    if (!m_project) {
        return 0;
    }
    return m_project->storyTree()->count();
}

QVariant StoryModel::data(const QModelIndex &index, int role) const {

    if (!m_project) {
        return QVariant();
    }

    StoryItem *item = m_project->storyTree()->itemAt(index.row());
    if (!item) {
        return QVariant();
    }

    switch (role) {
        case Qt::UserRole:
            return QVariant(item->handle());
            break;
        case Qt::DisplayRole:
            return QVariant(item->toJson());
            break;
        default:
            return QVariant();
            break;
    }
}

} // namespace Collett
