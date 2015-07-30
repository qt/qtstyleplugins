TEMPLATE = subdirs
SUBDIRS = \
    cleanlooks \
    motif \
    plastique

packagesExist(gconf-2.0 gtk+-2.0 x11) {
    SUBDIRS += gtk2
}
