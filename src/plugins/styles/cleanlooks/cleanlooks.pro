TARGET  = qcleanlooksstyle
load(qt_plugin)

QT = core gui widgets

HEADERS += qcleanlooksstyle.h
SOURCES += qcleanlooksstyle.cpp
SOURCES += plugin.cpp

include(../shared/shared.pri)

OTHER_FILES += cleanlooks.json

DESTDIR = $$QT.gui.plugins/styles
target.path += $$[QT_INSTALL_PLUGINS]/styles
INSTALLS += target
