TARGET  = qplastiquestyle
PLUGIN_TYPE = styles
load(qt_plugin)

QT = core core-private gui gui-private widgets

HEADERS += qplastiquestyle.h
SOURCES += qplastiquestyle.cpp
SOURCES += plugin.cpp

include(../shared/shared.pri)

OTHER_FILES += plastique.json
