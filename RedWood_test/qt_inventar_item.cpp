//-----------------------------------------------------------------------------
#include "qt_inventar_item.h"
//-----------------------------------------------------------------------------
qt_inventar_item::qt_inventar_item(QWidget *parent) :
    QWidget(parent),
    predmet_count(0)
//    img(10, 10, QImage::Format_RGB32)
{
    predmet.set_predmet_type(PREDMET_TYPE::UNKNOW_PREDMET);
/*
    int img_width;
    int img_height;

    if (width() < height())
    {
        img_width  = width();
        img_height = img_width;
    }
    else
    {
        img_width = height();
        img_height = img_width;
    }
    QImage* pimg = new QImage (img_width, img_height, QImage::Format_RGB32);
*/
//    img.fill(palette().window().color());

    widget_layout.setMargin(0);
    widget_layout.setSpacing(0);

//    lable_predmet_img.setFixedSize(img.size());
//    lable_predmet_img.setPixmap(QPixmap::fromImage(img));

//    widget_layout.addWidget(&lable_predmet_img);
    widget_layout.addWidget(&predmet);

    label_predmet_qty.setAlignment(Qt::AlignRight | Qt::AlignBottom);
    if (predmet_count > 0) label_predmet_qty.setNum(predmet_count);

    widget_layout.addWidget(&label_predmet_qty);

    setLayout(&widget_layout);
}
//-----------------------------------------------------------------------------
void qt_inventar_item::set_predmet_count(int new_count)
{
    predmet_count = new_count;
    if (predmet_count > 0) label_predmet_qty.setNum(predmet_count);
    else label_predmet_qty.setText("");
}
//-----------------------------------------------------------------------------
void qt_inventar_item::set_predmet(qt_predmet &new_predmet)
{
    predmet.setFixedSize(width(), height());
    predmet.copy_predmet(new_predmet);
    apend_one_predmet();
}
//-----------------------------------------------------------------------------
void qt_inventar_item::apend_one_predmet(void)
{
    if (predmet.get_predmet_type() != PREDMET_TYPE::UNKNOW_PREDMET)
    {
        predmet_count++;
        label_predmet_qty.setNum(predmet_count);
    }
}
//-----------------------------------------------------------------------------
void qt_inventar_item::remove_one_predmet(void)
{
    predmet_count--;
    if (predmet_count < 1)
    {
        predmet_count = 0;
        label_predmet_qty.setText("");
        predmet.set_predmet_type(PREDMET_TYPE::UNKNOW_PREDMET);
    }
    else
    {
        label_predmet_qty.setNum(predmet_count);
    }
}
//-----------------------------------------------------------------------------
QDataStream& operator <<(QDataStream &out, qt_inventar_item &inventar_item)
{
    PREDMET_TYPE predmet_type;
    QString      predmet_img;
    int          count;

    predmet_type = inventar_item.get_predmet_type();
    predmet_img  = inventar_item.get_predmet_img();
    count        = inventar_item.get_predmet_count();

//    out << inventar_item.get_predmet() << count;
    out << predmet_type << predmet_img << count;

    return out;
}
//-----------------------------------------------------------------------------
QDataStream& operator >>(QDataStream &in, qt_inventar_item &inventar_item)
{
//    PREDMET_TYPE predmet_type;
//    QString      predmet_img;
    int          count;
    qt_predmet   predmet;

    in >> predmet >> count;

    inventar_item.set_predmet(predmet);
    inventar_item.set_predmet_count(count);

    return in;
}
//-----------------------------------------------------------------------------
