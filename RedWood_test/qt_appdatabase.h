//-----------------------------------------------------------------------------
#ifndef QT_APPDATABASE_H
#define QT_APPDATABASE_H
//-----------------------------------------------------------------------------
#include <QObject>
#include <QSqlDatabase>
//-----------------------------------------------------------------------------
#include <qt_inventar_item.h>
//-----------------------------------------------------------------------------
class qt_appDataBase : public QObject
{
    Q_OBJECT
public:
    explicit qt_appDataBase(QObject *parent = nullptr);
    ~qt_appDataBase(void);

    void db_connect(void);
    void db_close  (void);
    void              db_write_item(const int row, const int col, qt_inventar_item &item);
    qt_inventar_item* db_read_item (const int row, const int col);

private:
    const int col_count = 3;
    const int row_count = 3;

    const QString db_name = QString::fromUtf8("redwoodtest.sqlite");
    QSqlDatabase db;

signals:

};
//-----------------------------------------------------------------------------
#endif // QT_APPDATABASE_H
//-----------------------------------------------------------------------------
