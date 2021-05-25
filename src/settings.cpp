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

#include "collett.h"
#include "settings.h"

#define CNF_MAIN_WINDOW_SIZE        "GuiMain/windowSize"
#define CNF_MAIN_SPLIT_TREE_WIDTH   "GuiMain/splitTreeWidth"
#define CNF_MAIN_SPLIT_EDITOR_WIDTH "GuiMain/splitEditorWidth"

#include <QCoreApplication>
#include <QList>
#include <QSettings>
#include <QSize>
#include <QVariant>

#include <QDebug>

namespace Collett {

/*
    Private Class Declaration
    =========================
*/

class ColSettingsPrivate
{
public:
    static ColSettings *instance;

    ColSettingsPrivate() {};
    ~ColSettingsPrivate() {};

    QSize mainWindowSize;
    int   mainSplitTreeWidth;
    int   mainSplitEditorWidth;
};

/*
    Public Class Contruction/Deconstruction
    =======================================
*/

ColSettings *ColSettingsPrivate::instance = nullptr;

ColSettings *ColSettings::instance() {
    if (nullptr == ColSettingsPrivate::instance) {
        ColSettingsPrivate::instance = new ColSettings();
        qDebug() << "ColSettings instance created";
    }
    return ColSettingsPrivate::instance;
}

ColSettings::ColSettings() : d_ptr(new ColSettingsPrivate()) {

    Q_D(ColSettings);

    // Load Settings
    QSettings mainConf;

    d->mainWindowSize       = mainConf.value(CNF_MAIN_WINDOW_SIZE,        QSize(1200, 800)).toSize();
    d->mainSplitTreeWidth   = mainConf.value(CNF_MAIN_SPLIT_TREE_WIDTH,   QVariant(300)).toInt();
    d->mainSplitEditorWidth = mainConf.value(CNF_MAIN_SPLIT_EDITOR_WIDTH, QVariant(900)).toInt();

    // Check Values
    if (d->mainWindowSize.width() < 400) {
        d->mainWindowSize.setWidth(400);
    }
    if (d->mainWindowSize.height() < 300) {
        d->mainWindowSize.setHeight(300);
    }
}

ColSettings::~ColSettings() {
    flushSettings();
}

/*
    Public Class Methods
    ====================
*/

void ColSettings::flushSettings() {
    Q_D(ColSettings);

    QSettings mainConf;

    mainConf.setValue(CNF_MAIN_WINDOW_SIZE,        QVariant(d->mainWindowSize));
    mainConf.setValue(CNF_MAIN_SPLIT_TREE_WIDTH,   QVariant(d->mainSplitTreeWidth));
    mainConf.setValue(CNF_MAIN_SPLIT_EDITOR_WIDTH, QVariant(d->mainSplitEditorWidth));

    qDebug() << "ColSettings values saved";

    return;
}

/*
    Setter Functions
    ================
*/

void ColSettings::setMainWindowSize(const QSize size) {
    Q_D(ColSettings);
    d->mainWindowSize = size;
    return;
}

void ColSettings::setMainSplitSizes(const QList<int> &sizes) {
    Q_D(ColSettings);
    if (sizes.length() > 0) {
        d->mainSplitTreeWidth = sizes.at(0);
    }
    if (sizes.length() > 1) {
        d->mainSplitEditorWidth = sizes.at(1);
    }
}

/*
    Getter Functions
    ================
*/

QSize ColSettings::mainWindowSize() const {
    Q_D(const ColSettings);
    return d->mainWindowSize;
}

QList<int> ColSettings::mainSplitSizes() const {
    Q_D(const ColSettings);
    QList<int> sizes;
    sizes.append(d->mainSplitTreeWidth);
    sizes.append(d->mainSplitEditorWidth);
    return sizes;
}

} // namespace Collett
