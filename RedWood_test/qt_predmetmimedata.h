//-----------------------------------------------------------------------------
#ifndef QT_PREDMETMIMEDATA_H
#define QT_PREDMETMIMEDATA_H
//-----------------------------------------------------------------------------
#include <QMimeData>
#include <QString>
//-----------------------------------------------------------------------------
#include "qt_predmet.h"
//-----------------------------------------------------------------------------
class qt_predmetMimeData : public QMimeData
{
public:
    qt_predmetMimeData();
    virtual ~qt_predmetMimeData();

    static QString mimeType();
    void setPredmet(qt_predmet* ppredmet);
    qt_predmet* predmet() const;
};
//-----------------------------------------------------------------------------
#endif // QT_PREDMETMIMEDATA_H
//-----------------------------------------------------------------------------
