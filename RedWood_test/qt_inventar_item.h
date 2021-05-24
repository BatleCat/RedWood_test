//-----------------------------------------------------------------------------
#ifndef QT_INVENTAR_ITEM_H
#define QT_INVENTAR_ITEM_H
//-----------------------------------------------------------------------------
#include <QWidget>
#include <QString>
#include <QLabel>
#include <QVBoxLayout>
//-----------------------------------------------------------------------------
#include "qt_predmet.h"
//-----------------------------------------------------------------------------
class qt_inventar_item : public QWidget
{
    Q_OBJECT
public:
    explicit qt_inventar_item(QWidget *parent = nullptr);

    void            set_predmet_count(int new_count);
    int             get_predmet_count(void)                 { return predmet_count; }
    void            set_predmet(qt_predmet &new_predmet);
//    qt_predmet&     get_predmet(void)                       { return predmet; }
    PREDMET_TYPE    get_predmet_type(void)                  { return predmet.get_predmet_type(); }
    QString         get_predmet_img(void)                   { return predmet.get_predmet_img (); }
    QString         get_predmet_name(void)                  { return predmet.get_predmet_name(); }

private:
    int         predmet_count;
    qt_predmet  predmet;
    QLabel      label_predmet_qty;
    QVBoxLayout widget_layout;

signals:

public slots:
    void apend_one_predmet(void);
    void remove_one_predmet(void);
};
//-----------------------------------------------------------------------------
QDataStream& operator <<(QDataStream &out, qt_inventar_item &inventar_item);
QDataStream& operator >>(QDataStream &in,  qt_inventar_item &inventar_item);
//-----------------------------------------------------------------------------
#endif // QT_INVENTAR_ITEM_H
//-----------------------------------------------------------------------------
