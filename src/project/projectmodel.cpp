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

#include "projectmodel.h"

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QObject>
#include <QVariant>

namespace Collett {

ProjectModel::ProjectModel(Project *project, QObject *parent)
    : m_project(project), QAbstractItemModel(parent)
{
}

QModelIndex ProjectModel::index(int row, int column, const QModelIndex &parent) const {
    return QModelIndex();
}

QModelIndex ProjectModel::parent(const QModelIndex &index) const {
    return QModelIndex();
}

int ProjectModel::rowCount(const QModelIndex &parent) const {
    return 0;
}

int ProjectModel::columnCount(const QModelIndex &parent) const {
    return 2;
}

QVariant ProjectModel::data(const QModelIndex &index, int role) const {
    return QVariant();
}

} // namespace Collett
