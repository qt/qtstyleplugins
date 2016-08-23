/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtWidgets module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QGTKSTYLE_P_P_H
#define QGTKSTYLE_P_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtCore/qglobal.h>

#include <QtCore/qstring.h>
#include <QtCore/qstringbuilder.h>
#include <QtCore/qcoreapplication.h>

#include <QtWidgets/QFileDialog>

#include "qgtkstyle_p.h"
#include <private/qcommonstyle_p.h>
#include "qgtkglobal_p.h"

QT_BEGIN_NAMESPACE

class QHashableLatin1Literal
{
public:
    int size() const { return m_size; }
    const char *data() const { return m_data; }

#ifdef __SUNPRO_CC
        QHashableLatin1Literal(const char* str)
        : m_size(strlen(str)), m_data(str) {}
#else
    template <int N>
        QHashableLatin1Literal(const char (&str)[N])
        : m_size(N - 1), m_data(str) {}
#endif

    QHashableLatin1Literal(const QHashableLatin1Literal &other)
        : m_size(other.m_size), m_data(other.m_data)
    {}

    QHashableLatin1Literal &operator=(const QHashableLatin1Literal &other)
    {
        if (this == &other)
            return *this;
        *const_cast<int *>(&m_size) = other.m_size;
        *const_cast<char **>(&m_data) = const_cast<char *>(other.m_data);
        return *this;
    }

    QString toString() const { return QString::fromLatin1(m_data, m_size); }

    static QHashableLatin1Literal fromData(const char *str)
    {
        return QHashableLatin1Literal(str, qstrlen(str));
    }

private:
    QHashableLatin1Literal(const char *str, int length)
        : m_size(length), m_data(str)
    {}

    const int m_size;
    const char *m_data;
};

bool operator==(const QHashableLatin1Literal &l1, const QHashableLatin1Literal &l2);
inline bool operator!=(const QHashableLatin1Literal &l1, const QHashableLatin1Literal &l2) { return !operator==(l1, l2); }
uint qHash(const QHashableLatin1Literal &key);

typedef void (*Ptr_ubuntu_gtk_set_use_overlay_scrollbar) (gboolean);

class QGtkPainter;
class QGtkStylePrivate;

class QGtkStyleFilter : public QObject
{
public:
    QGtkStyleFilter(QGtkStylePrivate* sp)
        : stylePrivate(sp)
    {}
private:
    QGtkStylePrivate* stylePrivate;
    bool eventFilter(QObject *obj, QEvent *e) Q_DECL_OVERRIDE;
};

typedef enum {
  GNOME_ICON_LOOKUP_FLAGS_NONE = 0,
  GNOME_ICON_LOOKUP_FLAGS_EMBEDDING_TEXT = 1<<0,
  GNOME_ICON_LOOKUP_FLAGS_SHOW_SMALL_IMAGES_AS_THEMSELVES = 1<<1,
  GNOME_ICON_LOOKUP_FLAGS_ALLOW_SVG_AS_THEMSELVES = 1<<2
} GnomeIconLookupFlags;

typedef enum {
  GNOME_ICON_LOOKUP_RESULT_FLAGS_NONE = 0,
  GNOME_ICON_LOOKUP_RESULT_FLAGS_THUMBNAIL = 1<<0
} GnomeIconLookupResultFlags;

struct GnomeThumbnailFactory;

class QGtkStylePrivate : public QCommonStylePrivate
{
    Q_DECLARE_PUBLIC(QGtkStyle)
public:
    QGtkStylePrivate();
    ~QGtkStylePrivate();

    QGtkStyleFilter filter;

    static QGtkPainter* gtkPainter(QPainter *painter = 0);
    static GtkWidget* gtkWidget(const QHashableLatin1Literal &path);
    static GtkStyle* gtkStyle(const QHashableLatin1Literal &path = QHashableLatin1Literal("GtkWindow"));
    static void gtkWidgetSetFocus(GtkWidget *widget, bool focus);

    virtual void initGtkMenu() const;
    virtual void initGtkTreeview() const;
    virtual void initGtkWidgets() const;

    static void cleanupGtkWidgets();

    static bool isKDE4Session();
    void applyCustomPaletteHash();
    static QFont getThemeFont();
    static bool isThemeAvailable() { return gtkStyle() != 0; }

    static QString getThemeName();
    virtual int getSpinboxArrowSize() const;

    virtual QPalette gtkWidgetPalette(const QHashableLatin1Literal &gtkWidgetName) const;

    static Ptr_ubuntu_gtk_set_use_overlay_scrollbar ubuntu_gtk_set_use_overlay_scrollbar;

protected:
    typedef QHash<QHashableLatin1Literal, GtkWidget*> WidgetMap;

    static inline void destroyWidgetMap()
    {
        cleanupGtkWidgets();
        delete widgetMap;
        widgetMap = 0;
    }

    static inline WidgetMap *gtkWidgetMap()
    {
        if (!widgetMap) {
            widgetMap = new WidgetMap();
            qAddPostRoutine(destroyWidgetMap);
        }
        return widgetMap;
    }

    static QStringList extract_filter(const QString &rawFilter);

    virtual GtkWidget* getTextColorWidget() const;
    static void setupGtkWidget(GtkWidget* widget);
    static void addWidgetToMap(GtkWidget* widget);
    static void addAllSubWidgets(GtkWidget *widget, gpointer v = 0);
    static void addWidget(GtkWidget *widget);
    static void removeWidgetFromMap(const QHashableLatin1Literal &path);

    virtual void init();

    enum {
        menuItemFrame        =  2, // menu item frame width
        menuItemHMargin      =  3, // menu item hor text margin
        menuArrowHMargin     =  6, // menu arrow horizontal margin
        menuItemVMargin      =  2, // menu item ver text margin
        menuRightBorder      = 15, // right border on menus
        menuCheckMarkWidth   = 12  // checkmarks width on menus
    };

private:
    static QList<QGtkStylePrivate *> instances;
    static WidgetMap *widgetMap;
    friend class QGtkStyleUpdateScheduler;
};

// Helper to ensure that we have polished all our gtk widgets
// before updating our own palettes
class QGtkStyleUpdateScheduler : public QObject
{
    Q_OBJECT
public slots:
    void updateTheme();
};

QT_END_NAMESPACE

#endif // QGTKSTYLE_P_P_H
