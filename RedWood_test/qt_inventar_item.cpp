//-----------------------------------------------------------------------------
#include "qt_inventar_item.h"
//-----------------------------------------------------------------------------
qt_inventar_item::qt_inventar_item(QWidget *parent) :
    QWidget(parent),
    predmet_count(0),
    img(10, 10, QImage::Format_RGB32)
{
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
    img.fill(palette().window().color());

    widget_layout.setMargin(0);
    widget_layout.setSpacing(0);

    lable_predmet_img.setFixedSize(img.size());
    lable_predmet_img.setPixmap(QPixmap::fromImage(img));

    widget_layout.addWidget(&lable_predmet_img);

    lable_predmet_qty.setAlignment(Qt::AlignRight | Qt::AlignBottom);
    if (predmet_count > 0) lable_predmet_qty.setNum(predmet_count);

    widget_layout.addWidget(&lable_predmet_qty);

    setLayout(&widget_layout);
}
//-----------------------------------------------------------------------------
void qt_inventar_item::apend_one_predmet(void)
{
    predmet_count++;
    lable_predmet_qty.setNum(predmet_count);
}
//-----------------------------------------------------------------------------
void qt_inventar_item::remove_one_predmet(void)
{
    predmet_count--;
    if (predmet_count < 1)
    {
        predmet_count = 0;
        lable_predmet_qty.setText("");
    }
    else
    {
        lable_predmet_qty.setNum(predmet_count);
    }
}
//-----------------------------------------------------------------------------
QDataStream& operator <<(QDataStream &out, const qt_inventar_item &inventar_item)
{
    int count = inventar_item.get_predmet_count();
    out <<  << inventar_item.get_predmet_descripton();
    return out;
}
//-----------------------------------------------------------------------------
QDataStream& operator >>(QDataStream &in, qt_inventar_item &inventar_item)
{

}
//-----------------------------------------------------------------------------
