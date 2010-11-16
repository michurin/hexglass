#
# HexGlass is a Tetris-like puzzle game.
#
# Project homepage: http://hexglass.googlecode.com/
#
# Copyright (C) 2010 Alexey Michurin <a.michurin@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.
#

VER_MAJ = 1
VER_MIN = 1
VER_PAT = 0

VERSION = $${VER_MAJ}.$${VER_MIN}.$${VER_PAT}

TEMPLATE = app

QT += core gui

# QMAKE_CXXFLAGS = -Wextra -Weffc++
# QMAKE_CXXFLAGS_RELEASE = -Wextra -Weffc++
# DEFINES += EXTRA_CONTROL

CONFIG += release
CONFIG += qt
CONFIG += warn_on
#CONFIG += debug

OBJECTS_DIR = build
MOC_DIR = build
RCC_DIR = build

DEFINES += HG_VERSION=\"$${VERSION}\"

TARGET = hexglass

INCLUDEPATH += \
             src \
             src/control \
             src/logic \
             src/widgets

RESOURCES += resources/hexglass.qrc \
             resources/hexglass_symbian.qrc

HEADERS   += src/hexglass_symbian.h \
             src/logic/figure.h \
             src/logic/abstract_place.h \
             src/logic/lplace.h \
             src/logic/pplace.h \
             src/logic/figure_iter.h \
             src/logic/figure_trans.h \
             src/logic/figures_bank.h \
             src/control/configuration.h \
             src/control/controller.h \
             src/control/freeze_proxy.h \
             src/control/skin.h \
             src/widgets/dialogs.h \
             src/widgets/displaywidget.h \
             src/widgets/glasswidget.h \
             src/widgets/headwidget.h \
             src/widgets/previewwidget.h \
             src/widgets/scorewidget.h \
             src/widgets/window.h \
             src/widgets/SymbianMainWindow.h
SOURCES   += src/hexglass_symbian.cpp \
             src/logic/figure.cpp \
             src/logic/abstract_place.cpp \
             src/logic/lplace.cpp \
             src/logic/pplace.cpp \
             src/logic/figure_iter.cpp \
             src/logic/figure_trans.cpp \
             src/logic/figures_bank.cpp \
             src/control/configuration.cpp \
             src/control/controller.cpp \
             src/control/freeze_proxy.cpp \
             src/control/skin.cpp \
             src/widgets/dialogs.cpp \
             src/widgets/displaywidget.cpp \
             src/widgets/glasswidget.cpp \
             src/widgets/headwidget.cpp \
             src/widgets/previewwidget.cpp \
             src/widgets/scorewidget.cpp \
             src/widgets/window.cpp \
             src/widgets/SymbianMainWindow.cpp

TRANSLATIONS = translations/hexglass_be.ts \
               translations/hexglass_ca.ts \
               translations/hexglass_es.ts \
               translations/hexglass_ru.ts \
               translations/hexglass_zh.ts
CODECFORSRC  = UTF-8

symbian: {
    ICON = resources/symbian/icon.svg
}

target.path += $$[QT_INSTALL_BINS]
INSTALLS += target

###################################################
