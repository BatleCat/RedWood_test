//-----------------------------------------------------------------------------
#include "qt_predmet.h"
//-----------------------------------------------------------------------------
qt_predmet::qt_predmet(QWidget *parent) :
    QWidget(parent),
    predmet_type(UNKNOW_PREDMET)
{

}
//-----------------------------------------------------------------------------
void qt_predmet::copy_predmet(qt_predmet &src_predmet)
{
    predmet_type = src_predmet.predmet_type;
    predmet_img = src_predmet.predmet_img;
}
//-----------------------------------------------------------------------------
QString qt_predmet::get_predmet_name()
{
    QString name;
    switch (predmet_type)
    {
        case UNKNOW_PREDMET:
        {
            name = QString::fromUtf8("Неизвестный");
            break;
        }
        case GREEN_APPLE:
        {
            name = QString::fromUtf8("Зеленое яблоко");
            break;
        }
        case RED_APPLE:
        {
            name = QString::fromUtf8("Красное яблоко");
            break;
        }
        default:
        {
            name = QString::fromUtf8("Неизвестный");
            break;
        }
    }
    return name;
}
//-----------------------------------------------------------------------------
QDataStream& operator <<(QDataStream &out, const PREDMET_TYPE &predmet_type)
{
    out.writeRawData((char*)(&predmet_type), sizeof(PREDMET_TYPE));
    return out;
}
//-----------------------------------------------------------------------------
QDataStream& operator >>(QDataStream &in, PREDMET_TYPE &predmet_type)
{
    in.readRawData((char*)(&predmet_type), sizeof(PREDMET_TYPE));
    return in;
}
//-----------------------------------------------------------------------------
QDataStream& operator <<(QDataStream &out, qt_predmet &predmet)
{
    QString      img  = predmet.get_predmet_img();
    PREDMET_TYPE type = predmet.get_predmet_type();

    out << img << type;

    return out;
}
//-----------------------------------------------------------------------------
QDataStream& operator >>(QDataStream &in, qt_predmet &predmet)
{
    QString      img;
    PREDMET_TYPE type;

    in >> img >> type;

    predmet.set_predmet_img(img);
    predmet.set_predmet_type(type);

    return in;
}
//-----------------------------------------------------------------------------
