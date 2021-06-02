//-----------------------------------------------------------------------------
#include "qt_predmet.h"
//-----------------------------------------------------------------------------
#include <QImage>
#include <QDrag>
#include <QApplication>
#include <QMouseEvent>
//#include <QDebug>
//-----------------------------------------------------------------------------
#include "qt_predmetmimedata.h"
//-----------------------------------------------------------------------------
qt_predmet::qt_predmet(QWidget *parent) :
    QWidget(parent),
    predmet_type(PREDMET_TYPE::UNKNOW_PREDMET),
    predmet_img(QString::fromUtf8(""))
{
    QImage *img = new QImage( width(), height(), QImage::Format_RGB32 );
    img->fill( palette().background().color() );

    widget_layout.setMargin(0);
    widget_layout.setSpacing(0);

    label_predmet_img.setFixedSize( img->size() );
    label_predmet_img.setPixmap( QPixmap::fromImage(*img) );

    widget_layout.addWidget(&label_predmet_img);

    setLayout(&widget_layout);

    delete img;
}
//-----------------------------------------------------------------------------
void qt_predmet::set_predmet_type(PREDMET_TYPE type)
{
    predmet_type = type;
    if ( predmet_type == PREDMET_TYPE::UNKNOW_PREDMET)
    {
        QPixmap* pix_img = new QPixmap( size() );
        pix_img->fill( palette().window().color() );
        label_predmet_img.setFixedSize( pix_img->size() );
        label_predmet_img.setPixmap( (*pix_img) );
    }
}
//-----------------------------------------------------------------------------
void qt_predmet::set_predmet_img(QString img_string)
{
    QImage img;

    predmet_img = img_string;

    if ( img.load(predmet_img) )
    {
        QImage img1 = img.scaled( size(), Qt::KeepAspectRatio );
        label_predmet_img.setFixedSize( img1.size() );
        label_predmet_img.setPixmap( QPixmap::fromImage(img1) );
    }
    else
    {
        QPixmap* pix_img = new QPixmap( size() );
        pix_img->fill( palette().window().color() );
        label_predmet_img.setFixedSize( pix_img->size() );
        label_predmet_img.setPixmap( (*pix_img) );
    }
}
//-----------------------------------------------------------------------------
void qt_predmet::copy_predmet(qt_predmet &src_predmet)
{
    predmet_type = src_predmet.get_predmet_type();
    set_predmet_img( src_predmet.get_predmet_img() );
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
void qt_predmet::startDrag()
{
    QImage img;
    QImage img1;

    img.load(predmet_img);
    img1 = img.scaled( size(), Qt::KeepAspectRatio );

    qt_predmetMimeData* pMimeData = new qt_predmetMimeData;
    pMimeData->setPredmet(this);
    QDrag* pDrag = new QDrag(this);
    pDrag->setMimeData(pMimeData);
    pDrag->setPixmap( QPixmap::fromImage(img1) );
    pDrag->exec(Qt::MoveAction);
}
//-----------------------------------------------------------------------------
void qt_predmet::mousePressEvent(QMouseEvent* pme)
{
    if (pme->button() == Qt::LeftButton)
    {
        m_ptDragPos = pme->pos();
    }
    QWidget::mousePressEvent(pme);
}
//-----------------------------------------------------------------------------
void qt_predmet::mouseMoveEvent (QMouseEvent* pme)
{
    if (pme->buttons() & Qt::LeftButton)
    {
        int distance = ( pme->pos() - m_ptDragPos ).manhattanLength();
        if (distance > QApplication::startDragDistance())
        {
            startDrag();
        }
    }
    QWidget::mouseMoveEvent(pme);
}
//-----------------------------------------------------------------------------
QDataStream& operator <<(QDataStream &out, const PREDMET_TYPE &predmet_type)
{
    out.writeRawData( (char*)(&predmet_type), sizeof(PREDMET_TYPE) );
    return out;
}
//-----------------------------------------------------------------------------
QDataStream& operator >>(QDataStream &in, PREDMET_TYPE &predmet_type)
{
    in.readRawData( (char*)(&predmet_type), sizeof(PREDMET_TYPE) );
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
