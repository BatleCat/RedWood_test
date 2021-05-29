//-----------------------------------------------------------------------------
#include "qt_inventar_item.h"
//-----------------------------------------------------------------------------
#include "qt_predmet.h"
#include <QImage>
#include <QDrag>
#include <QApplication>
//#include <QDebug>
//-----------------------------------------------------------------------------
#include "qt_predmetmimedata.h"
#include "qt_inventar_itemmimedata.h"
//-----------------------------------------------------------------------------
qt_inventar_item::qt_inventar_item(qt_predmet *parent) :
    qt_predmet(parent),
    predmet_count(0)
{
    set_predmet_type(PREDMET_TYPE::UNKNOW_PREDMET);

    label_predmet_qty.setAlignment(Qt::AlignRight | Qt::AlignBottom);
//    label_predmet_qty.setFocusPolicy(Qt::NoFocus);
//    label_predmet_qty.setFocus(Qt::FocusReason::NoFocusReason);
//    label_predmet_qty.setDisabled(false);
    if (predmet_count > 0) label_predmet_qty.setNum(predmet_count);

    widget_layout.addWidget(&label_predmet_qty);

    setAcceptDrops(true);
}
//-----------------------------------------------------------------------------
void qt_inventar_item::set_predmet_count(int new_count)
{
    predmet_count = new_count;
    if (predmet_count > 0) label_predmet_qty.setNum(predmet_count);
    else
    {
        predmet_count = 0;
        label_predmet_qty.setText("");
        set_predmet_type(PREDMET_TYPE::UNKNOW_PREDMET);
    }
}
//-----------------------------------------------------------------------------
void qt_inventar_item::set_predmet(qt_predmet &new_predmet)
{
    setFixedSize(width(), height());
    copy_predmet(new_predmet);
    apend_one_predmet();
}
//-----------------------------------------------------------------------------
void qt_inventar_item::startDrag()
{
    QImage img;
    QImage img1;

    img.load( get_predmet_img() );
    img1 = img.scaled( size(), Qt::KeepAspectRatio );

    qt_inventar_itemMimeData* pMimeData = new qt_inventar_itemMimeData;
    pMimeData->setInventarItem(this);
    QDrag* pDrag = new QDrag(this);
    pDrag->setMimeData(pMimeData);
    pDrag->setPixmap( QPixmap::fromImage(img1) );
    pDrag->exec(Qt::MoveAction);
}
//-----------------------------------------------------------------------------
void qt_inventar_item::mousePressEvent(QMouseEvent* pme)
{
    if (pme->button() == Qt::LeftButton)
    {
        m_ptDragPos = pme->pos();
    }
    if (pme->button() == Qt::RightButton)
    {
        remove_one_predmet();
    }
    QWidget::mousePressEvent(pme);
}
//-----------------------------------------------------------------------------
void qt_inventar_item::mouseMoveEvent (QMouseEvent* pme)
{
    if ( (pme->buttons() & Qt::LeftButton)
         && (predmet_count > 0) )
    {
        int distance = (pme->pos() - m_ptDragPos).manhattanLength();
        if (distance > QApplication::startDragDistance())
        {
            startDrag();
        }
    }
    QWidget::mouseMoveEvent(pme);
}
//-----------------------------------------------------------------------------
void qt_inventar_item::dragEnterEvent (QDragEnterEvent* pme)
{
    if (  ( pme->mimeData()->hasFormat(qt_predmetMimeData::mimeType()) )
       || ( pme->mimeData()->hasFormat(qt_inventar_itemMimeData::mimeType()) ) )
    {
        pme->acceptProposedAction();
    }
}
//-----------------------------------------------------------------------------
void qt_inventar_item::dropEvent(QDropEvent* pme)
{
    if ( pme->mimeData()->hasFormat(qt_inventar_itemMimeData::mimeType()) )
    {
        const qt_inventar_itemMimeData* pmmd = dynamic_cast<const qt_inventar_itemMimeData*>( pme->mimeData() );
        if (pmmd)
        {
            // если ячейка пустая
            if (get_predmet_type() == PREDMET_TYPE::UNKNOW_PREDMET)
            {
                qt_inventar_item* new_inventar_item = pmmd->inventarItem();
                set_predmet_type(new_inventar_item->get_predmet_type());
                set_predmet_img(new_inventar_item->get_predmet_img());
                set_predmet_count(new_inventar_item->get_predmet_count());
            }
            else // ячейка содержит предметы
            {
                int new_count = get_predmet_count();
                new_count += pmmd->inventarItem()->get_predmet_count();
                set_predmet_count(new_count);
            }
        }
    }
    else if ( pme->mimeData()->hasFormat(qt_predmetMimeData::mimeType()) )
    {
        const qt_predmetMimeData* pmmd = dynamic_cast<const qt_predmetMimeData*>( pme->mimeData() );
        if (pmmd)
        {
            set_predmet( *pmmd->predmet() );
        }
    }
}
//-----------------------------------------------------------------------------
void qt_inventar_item::apend_one_predmet(void)
{
    if (get_predmet_type() != PREDMET_TYPE::UNKNOW_PREDMET)
    {
        predmet_count++;
        set_predmet_count(predmet_count);
    }
}
//-----------------------------------------------------------------------------
void qt_inventar_item::remove_one_predmet(void)
{
    if (get_predmet_type() != PREDMET_TYPE::UNKNOW_PREDMET)
    {
        predmet_count--;
        set_predmet_count(predmet_count);
    }
    else
    {
        predmet_count = 0;
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

    out << predmet_type << predmet_img << count;

//    qDebug() << QString::fromUtf8("operator <<")
//             << inventar_item.get_predmet_type()
//             << inventar_item.get_predmet_img()
//             << inventar_item.get_predmet_count();

    return out;
}
//-----------------------------------------------------------------------------
QDataStream& operator >>(QDataStream &in, qt_inventar_item &inventar_item)
{
    PREDMET_TYPE predmet_type;
    QString      predmet_img;
    int          count;

    in >> predmet_type >> predmet_img >> count;

    inventar_item.set_predmet_type(predmet_type);
    inventar_item.set_predmet_img(predmet_img);
    inventar_item.set_predmet_count(count);

//    qDebug() << QString::fromUtf8("operator >>")
//             << inventar_item.get_predmet_type()
//             << inventar_item.get_predmet_img()
//             << inventar_item.get_predmet_count();

    return in;
}
//-----------------------------------------------------------------------------
