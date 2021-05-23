//-----------------------------------------------------------------------------
#ifndef QT_PREDMET_H
#define QT_PREDMET_H
//-----------------------------------------------------------------------------
#include <QWidget>
#include <QString>
#include <QLabel>
#include <QVBoxLayout>
#include <QDataStream>
//-----------------------------------------------------------------------------
typedef enum
{
    UNKNOW_PREDMET = 0,
    GREEN_APPLE,
    RED_APPLE
} PREDMET_TYPE;
//-----------------------------------------------------------------------------
QDataStream& operator <<(QDataStream &out, const PREDMET_TYPE &predmet_type);
QDataStream& operator >>(QDataStream &in, PREDMET_TYPE &predmet_type);
//-----------------------------------------------------------------------------
class qt_predmet : public QWidget
{
    Q_OBJECT
public:
    explicit qt_predmet(QWidget *parent = nullptr);

    void          set_predmet_type(PREDMET_TYPE type)   { predmet_type = type; }
    PREDMET_TYPE  get_predmet_type()                    { return predmet_type; }
    void          set_predmet_img(QString img_string);
    QString       get_predmet_img()                     { return predmet_img;  }
    void          copy_predmet(qt_predmet &src_predmet);
    QString       get_predmet_name();

private:
    PREDMET_TYPE predmet_type;
    QString      predmet_img;
    QLabel       lable_predmet_img;
    QVBoxLayout  widget_layout;

public:
signals:

};
//-----------------------------------------------------------------------------
QDataStream& operator <<(QDataStream &out, const qt_predmet &predmet);
QDataStream& operator >>(QDataStream &in, qt_predmet &predmet);
//-----------------------------------------------------------------------------
#endif // QT_PREDMET_H
//-----------------------------------------------------------------------------
