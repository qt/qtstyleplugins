TEMPLATE = subdirs
SUBDIRS = \
    cleanlooks \
    motif \
    plastique

greaterThan(QT_MAJOR_VERSION, 5) | greaterThan(QT_MINOR_VERSION, 6) {
    # only 5.7 or later
    SUBDIRS += bb10style
}

packagesExist(gtk+-2.0 x11) {
    SUBDIRS += gtk2
}
