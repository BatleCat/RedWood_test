//-----------------------------------------------------------------------------
#ifndef QT_INVENTAR_H
#define QT_INVENTAR_H
//-----------------------------------------------------------------------------
#include <QObject>
#include "qt_predmet.h"
//-----------------------------------------------------------------------------
class qt_inventar : public QObject
{
    Q_OBJECT
public:
    explicit qt_inventar(QObject *parent = nullptr);

private:
    int cell_num;
    int predmet_count;
    qt_predmet predmet;
    PREDMET_TYPE predmet_type;
    QString      predmet_img;

signals:

};
//-----------------------------------------------------------------------------
#endif // QT_INVENTAR_H
//-----------------------------------------------------------------------------
