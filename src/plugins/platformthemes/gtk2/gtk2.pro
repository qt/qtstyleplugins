TARGET = qgtk2

QT += core-private gui-private
greaterThan(QT_MAJOR_VERSION, 5)|greaterThan(QT_MINOR_VERSION, 7): \
    QT += theme_support-private
else: \
    QT += platformsupport-private

CONFIG += X11
CONFIG += link_pkgconfig
PKGCONFIG += gtk+-2.0

HEADERS += \
        qgtk2dialoghelpers.h \
        qgtk2theme.h

SOURCES += \
        main.cpp \
        qgtk2dialoghelpers.cpp \
        qgtk2theme.cpp \

PLUGIN_TYPE = platformthemes
PLUGIN_EXTENDS = -
PLUGIN_CLASS_NAME = QGtk2ThemePlugin
load(qt_plugin)
