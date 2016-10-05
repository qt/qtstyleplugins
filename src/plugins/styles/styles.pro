TEMPLATE = subdirs
SUBDIRS = \
    cleanlooks \
    motif \
    plastique \
    bb10style

packagesExist(gtk+-2.0 x11) {
    SUBDIRS += gtk2
}
