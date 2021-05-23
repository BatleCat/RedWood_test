//-----------------------------------------------------------------------------
#ifndef QT_INVENTAR_ITEM_H
#define QT_INVENTAR_ITEM_H
//-----------------------------------------------------------------------------
#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QVBoxLayout>
#include "qt_predmet.h"
//-----------------------------------------------------------------------------
class qt_inventar_item : public QWidget
{
    Q_OBJECT
public:
    explicit qt_inventar_item(QWidget *parent = nullptr);

    void        set_predmet_count(int new_count)    { predmet_count = new_count; }
    int         get_predmet_count()                 { return predmet_count; }
    void        set_predmet(qt_predmet);
    qt_predmet  get_predmet_descripton(void);

private:
    int         predmet_count;
    qt_predmet  predmet;
    QImage      img;
    QLabel      lable_predmet_img;
    QLabel      lable_predmet_qty;
    QVBoxLayout widget_layout;

signals:

public slots:
    void apend_one_predmet(void);
    void remove_one_predmet(void);
};
//-----------------------------------------------------------------------------
QDataStream& operator <<(QDataStream &out, const qt_inventar_item &inventar_item);
QDataStream& operator >>(QDataStream &in, qt_inventar_item &inventar_item);
//-----------------------------------------------------------------------------
#endif // QT_INVENTAR_ITEM_H
//-----------------------------------------------------------------------------
