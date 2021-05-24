//-----------------------------------------------------------------------------
#include "qt_predmet.h"
#include <QImage>
//-----------------------------------------------------------------------------
qt_predmet::qt_predmet(QWidget *parent) :
    QWidget(parent),
    predmet_type(UNKNOW_PREDMET)
{
    QImage *img = new QImage(width(), height(), QImage::Format_RGB32);
    img->fill(palette().window().color());

    widget_layout.setMargin(0);
    widget_layout.setSpacing(0);

    lable_predmet_img.setFixedSize( img->size() );
    lable_predmet_img.setPixmap( QPixmap::fromImage(*img) );

    widget_layout.addWidget(&lable_predmet_img);

    setLayout(&widget_layout);

    delete img;
}
//-----------------------------------------------------------------------------
void qt_predmet::set_predmet_img(QString img_string)
{
    QImage img;
    QImage img1;

    predmet_img = img_string;

    img.load(predmet_img);
    img1 = img.scaled( size(), Qt::KeepAspectRatio );

    lable_predmet_img.setFixedSize( img1.size() );
    lable_predmet_img.setPixmap( QPixmap::fromImage(img1) );
}
//-----------------------------------------------------------------------------
void qt_predmet::copy_predmet(qt_predmet &src_predmet)
{
    predmet_type = src_predmet.get_predmet_type();
    set_predmet_img(src_predmet.get_predmet_img());
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

    out << type << img;

    return out;
}
//-----------------------------------------------------------------------------
QDataStream& operator >>(QDataStream &in, qt_predmet &predmet)
{
    QString      img;
    PREDMET_TYPE type;

    in >> type >> img;

    predmet.set_predmet_type(type);
    predmet.set_predmet_img(img);

    return in;
}
//-----------------------------------------------------------------------------
