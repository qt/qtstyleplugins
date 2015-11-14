TEMPLATE = subdirs
SUBDIRS = \
    cleanlooks \
    motif \
    plastique \
    bb10style

packagesExist(gconf-2.0 gtk+-2.0 x11) {
    SUBDIRS += gtk2
}
