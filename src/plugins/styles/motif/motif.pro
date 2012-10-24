TARGET  = qmotifstyle
load(qt_plugin)

QT = core gui widgets

HEADERS += qmotifstyle.h
SOURCES += qmotifstyle.cpp
SOURCES += plugin.cpp

OTHER_FILES += motif.json

DESTDIR = $$QT.gui.plugins/styles
target.path += $$[QT_INSTALL_PLUGINS]/styles
INSTALLS += target
