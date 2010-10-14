#
# HexGlass is a Tetris-like puzzle game.
#
# Copyright (C) 2010 Alexey Michurin
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
VER_MIN = 0
VER_PAT = 8

VERSION = $${VER_MAJ}.$${VER_MIN}.$${VER_PAT}

TEMPLATE = app

QT += core gui

# QMAKE_CXXFLAGS = -Wextra -Weffc++
# QMAKE_CXXFLAGS_RELEASE = -Wextra -Weffc++
# DEFINES += EXTRA_CONTROL

CONFIG += release
CONFIG += qt
# CONFIG += warn_on
# CONFIG += debug

OBJECTS_DIR = build
MOC_DIR = build
RCC_DIR = build

DEFINES += HG_VERSION=\"$${VERSION}\"

TARGET = hexglass

RC_FILE = resources/hexglass.rc

INCLUDEPATH += \
             src \
             src/control \
             src/logic \
             src/widgets

RESOURCES += resources/hexglass.qrc

HEADERS   += src/hexglass.h \
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
             src/widgets/window.h
SOURCES   += src/hexglass.cpp \
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
             src/widgets/window.cpp

TRANSLATIONS = translations/hexglass_be.ts \
               translations/hexglass_ca.ts \
               translations/hexglass_es.ts \
               translations/hexglass_ru.ts \
               translations/hexglass_zh.ts
CODECFORSRC  = UTF-8

target.path += $$[QT_INSTALL_BINS]
INSTALLS += target

###################################################

SDIST_BUILD_DIR = build
SDIST_TARGET = $${SDIST_BUILD_DIR}/$${TARGET}-$${VERSION}
SDIST_DIR = $${SDIST_TARGET}
SDIST_FILE = $${SDIST_TARGET}.tar.gz

source_dist.target = sdist
source_dist.commands += '$(CHK_DIR_EXISTS) $${SDIST_DIR} && echo "REMOVE $${SDIST_DIR} MANUALY" && exit 22;'
source_dist.commands += '$(DEL_FILE) $${SDIST_FILE};'
source_dist.commands += '$(MKDIR) $${SDIST_DIR};'
source_dist.commands += 'tar cf - -T MANIFEST | tar xf - -C $${SDIST_DIR};'
source_dist.commands += 'tar cf - -C $${SDIST_BUILD_DIR} $${TARGET}-$${VERSION} | gzip -9c >$${SDIST_FILE}'

QMAKE_EXTRA_TARGETS += source_dist
