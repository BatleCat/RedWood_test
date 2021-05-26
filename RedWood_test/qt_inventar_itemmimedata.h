//-----------------------------------------------------------------------------
#ifndef QT_INVENTAR_ITEMMIMEDATA_H
#define QT_INVENTAR_ITEMMIMEDATA_H
//-----------------------------------------------------------------------------
#include <QMimeData>
#include <QString>
//-----------------------------------------------------------------------------
#include "qt_inventar_item.h"
//-----------------------------------------------------------------------------
class qt_inventar_itemMimeData : public QMimeData
{
public:
    qt_inventar_itemMimeData();
    virtual ~qt_inventar_itemMimeData();

    static QString mimeType();
    void setInventarItem(qt_inventar_item* pinventar_item);
    qt_inventar_item* inventarItem() const;
};
//-----------------------------------------------------------------------------
#endif // QT_INVENTAR_ITEMMIMEDATA_H
//-----------------------------------------------------------------------------
