TARGET  = qmotifstyle
PLUGIN_TYPE = styles
load(qt_plugin)

QT = core gui widgets

HEADERS += qcdestyle.h
HEADERS += qmotifstyle.h
SOURCES += qcdestyle.cpp
SOURCES += qmotifstyle.cpp
SOURCES += plugin.cpp

OTHER_FILES += motif.json
