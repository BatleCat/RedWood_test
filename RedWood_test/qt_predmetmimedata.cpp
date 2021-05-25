//-----------------------------------------------------------------------------
#include "qt_predmetmimedata.h"
//-----------------------------------------------------------------------------
#include <QByteArray>
#include <QDataStream>
//-----------------------------------------------------------------------------
qt_predmetMimeData::qt_predmetMimeData() : QMimeData()
{

}
//-----------------------------------------------------------------------------
qt_predmetMimeData::~qt_predmetMimeData()
{

}
//-----------------------------------------------------------------------------
QString qt_predmetMimeData::mimeType()
{
    return "application/predmet";
}
//-----------------------------------------------------------------------------
void qt_predmetMimeData::setPredmet(qt_predmet* ppredmet)
{
    QByteArray ba_data;
    QDataStream data_stream(&ba_data, QIODevice::WriteOnly);

    data_stream << *ppredmet;
    setData(mimeType(), ba_data);
}
//-----------------------------------------------------------------------------
qt_predmet* qt_predmetMimeData::predmet() const
{
    qt_predmet* ppredmet = new qt_predmet;
    QByteArray ba_data;
    QDataStream data_stream(&ba_data, QIODevice::ReadOnly);

    ba_data = data( mimeType() );
    data_stream >> *ppredmet;

    return ppredmet;
}
//-----------------------------------------------------------------------------
