//-----------------------------------------------------------------------------
#include "qt_inventar_itemmimedata.h"
//-----------------------------------------------------------------------------
#include <QByteArray>
#include <QDataStream>
//-----------------------------------------------------------------------------
qt_inventar_itemMimeData::qt_inventar_itemMimeData()
{

}
//-----------------------------------------------------------------------------
qt_inventar_itemMimeData::~qt_inventar_itemMimeData()
{

}
//-----------------------------------------------------------------------------
QString qt_inventar_itemMimeData::mimeType()
{
    return "application/inventar_item";
}
//-----------------------------------------------------------------------------
void qt_inventar_itemMimeData::setInventarItem(qt_inventar_item *pinventar_item)
{
    QByteArray ba_data;
    QDataStream data_stream(&ba_data, QIODevice::WriteOnly);

    data_stream << *pinventar_item;
    setData(mimeType(), ba_data);
}
//-----------------------------------------------------------------------------
qt_inventar_item* qt_inventar_itemMimeData::inventarItem() const
{
    qt_inventar_item* pinventar_item = new qt_inventar_item;
    QByteArray ba_data;
    QDataStream data_stream(&ba_data, QIODevice::ReadOnly);

    ba_data = data( mimeType() );
    data_stream >> *pinventar_item;

    return pinventar_item;
}
//-----------------------------------------------------------------------------
