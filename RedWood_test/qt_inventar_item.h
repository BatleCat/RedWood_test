//-----------------------------------------------------------------------------
#ifndef QT_INVENTAR_ITEM_H
#define QT_INVENTAR_ITEM_H
//-----------------------------------------------------------------------------
#include <QWidget>
#include <QString>
#include <QLabel>
#include <QVBoxLayout>
#include <QDataStream>
#include <QPoint>
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
//-----------------------------------------------------------------------------
#include "qt_predmet.h"
//-----------------------------------------------------------------------------
class qt_inventar_item : public qt_predmet
{
    Q_OBJECT
public:
    explicit      qt_inventar_item(qt_predmet *parent = nullptr);

    void          set_predmet_count(int new_count);
    int           get_predmet_count(void)                 { return predmet_count; }
    void          set_predmet(qt_predmet &new_predmet);

private:
    void          startDrag();

protected:
    virtual void  mousePressEvent(QMouseEvent* pme);
    virtual void  mouseMoveEvent (QMouseEvent* pme);
    virtual void  dragEnterEvent (QDragEnterEvent*pme);
    virtual void  dropEvent      (QDropEvent* pme);

protected:
    int           predmet_count;
    QLabel        label_predmet_qty;
    QPoint        m_ptDragPos;

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
