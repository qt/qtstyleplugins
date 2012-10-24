TARGET  = qplastiquestyle
load(qt_plugin)

QT = core core-private gui gui-private widgets

HEADERS += qplastiquestyle.h
SOURCES += qplastiquestyle.cpp
SOURCES += plugin.cpp

include(../shared/shared.pri)

OTHER_FILES += plastique.json

DESTDIR = $$QT.gui.plugins/styles
target.path += $$[QT_INSTALL_PLUGINS]/styles
INSTALLS += target
