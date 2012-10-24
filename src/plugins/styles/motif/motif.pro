TARGET  = qmotifstyle
load(qt_plugin)

QT = core gui widgets

HEADERS += qcdestyle.h
HEADERS += qmotifstyle.h
SOURCES += qcdestyle.cpp
SOURCES += qmotifstyle.cpp
SOURCES += plugin.cpp

OTHER_FILES += motif.json

DESTDIR = $$QT.gui.plugins/styles
target.path += $$[QT_INSTALL_PLUGINS]/styles
INSTALLS += target
