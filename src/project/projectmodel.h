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

#ifndef COL_PROJECTMODEL_H
#define COL_PROJECTMODEL_H

#include "project.h"

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QObject>

namespace Collett {

class ProjectModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit ProjectModel(Project *project, QObject *parent=nullptr);
    ~ProjectModel() {};

    QModelIndex index(int row, int column, const QModelIndex &parent=QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent=QModelIndex()) const;
    int columnCount(const QModelIndex &parent=QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const;

private:
    const Project *m_project;

};
} // namespace Collett

#endif // COL_PROJECTMODEL_H
