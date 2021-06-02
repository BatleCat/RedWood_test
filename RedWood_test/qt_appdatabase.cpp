//-----------------------------------------------------------------------------
#include "qt_appdatabase.h"
//-----------------------------------------------------------------------------
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QDebug>
#include <QString>
//-----------------------------------------------------------------------------
#include <qt_predmet.h>
#include <qt_inventar_item.h>
//-----------------------------------------------------------------------------
qt_appDataBase::qt_appDataBase(QObject *parent) : QObject(parent)
{
    db_connect();
}
//-----------------------------------------------------------------------------
qt_appDataBase::~qt_appDataBase(void)
{
    db_close();
}
//-----------------------------------------------------------------------------
void qt_appDataBase::db_connect(void)
{
    //------------------------------------------------------------------------
    // Создаю базу данных
    //------------------------------------------------------------------------
    db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName(db_name);
    db.setHostName("localhost");
    db.setUserName("user");
    db.setPassword("");
    if (!db.open())
    {
        qDebug() << QString::fromUtf8("Не могу открыть базу данных: ") << db.lastError().text();
        // throw some_err;
        return;
    }
    //------------------------------------------------------------------------
    QStringList lst = db.tables();
    //------------------------------------------------------------------------
    // Если в базе даннх нет таблицы predmet, то создаем ее
    //------------------------------------------------------------------------
    if ( !db.tables(QSql::Tables).contains( QString::fromUtf8("predmet") ) )
    {
        QSqlQuery query;
        //------------------------------------------------------------------------
        // Создаю таблицу predmet
        //-------------------------------------------------------------------------
        QString str = QString::fromUtf8
        (
            "CREATE TABLE predmet ( "
            "predmetId INTEGER PRIMARY KEY NOT NULL, "
            "type      INTEGER UNIQUE NOT NULL, "
            "image     TEXT, "
            "name      TEXT NOT NULL "
            ");"
        );
        if ( !query.exec(str) )
        {
            qDebug() << QString::fromUtf8("Ошибка создания таблицы predmet: ") << db.lastError().text();
            // throw some_err;
            return;
        }
        //------------------------------------------------------------------------
        // Заполняю таблицу predmet
        //-------------------------------------------------------------------------
        QString strF = QString::fromUtf8(
            "INSERT INTO predmet (predmetId, type, image, name) "
            "VALUES(%1, %2, '%3', '%4');"
        );

        str =   strF.arg("1")
                    .arg(int(PREDMET_TYPE::UNKNOW_PREDMET))
                    .arg(QString::fromUtf8(":/img/"))
                    .arg(QString::fromUtf8("Неизвестный"));
        if ( !query.exec(str) )
        {
            qDebug() << "Unable to make insert operation";
            // throw some_err;
            return;
        }

        str =   strF.arg("2")
                    .arg(int(PREDMET_TYPE::GREEN_APPLE))
                    .arg(QString::fromUtf8(":/img/green-apple.jpg"))
                    .arg(QString::fromUtf8("Зеленое яблоко"));
        query.exec(str);

        str =   strF.arg("3")
                    .arg(int(PREDMET_TYPE::RED_APPLE))
                    .arg(QString::fromUtf8(":/img/red-apple.jpg"))
                    .arg(QString::fromUtf8("Красное яблоко"));
        query.exec(str);

    }
    //------------------------------------------------------------------------
    // Если в базе даннх нет таблицы inventar, то создаем ее
    //------------------------------------------------------------------------
    if ( !db.tables(QSql::Tables).contains( QString::fromUtf8("inventar") ) )  // Если в базе даннх нет таблицы predmet, то создаем ее
    {
        QSqlQuery query;
        //------------------------------------------------------------------------
        query.exec("PRAGMA foreign_keys = ON;");
        //------------------------------------------------------------------------
        // Создаем таблицу inventar
        //-------------------------------------------------------------------------
        QString str = QString::fromUtf8
        (
            "CREATE TABLE inventar ( "
            "inventarId INTEGER PRIMARY KEY NOT NULL, "
            "row        INTEGER NOT NULL, "
            "col        INTEGER NOT NULL, "
            "predmetRef INTEGER NOT NULL, "
            "count      INTEGER NOT NULL, "
            "FOREIGN KEY(predmetRef) REFERENCES predmet(predmetId) "
            ");"
        );
        if ( !query.exec(str) )
        {
            qDebug() << QString::fromUtf8("Ошибка создания таблицы inventar: ") << db.lastError().text();
            // throw some_err;
            return;
        }
        //-------------------------------------------------------------------------
        // Добавляем данные в таблицу Инвентарь
        //-------------------------------------------------------------------------
        QString strF = QString::fromUtf8
                (
                    "INSERT INTO inventar (inventarId, row, col, predmetRef, count) "
                    "VALUES(%1, %2, %3, %4, %5);"
                );
        int row = 0;
        int col = 0;
        int count = 0;
        for (col = 0; col < col_count; col++)
        {
            for (row = 0; row < row_count; row++)
            {
                count++;
                str =   strF.arg(count)
                            .arg(row)
                            .arg(col)
                            .arg(1)
                            .arg(0);

                if (!query.exec(str))
                {
                    qDebug() << QString::fromUtf8("Не могу заполнить таблицу inventar!");
                    qDebug() << str;
                    // throw some_err;
                    return;
                }
            }
        }

    }

}
//-----------------------------------------------------------------------------
void qt_appDataBase::db_close  (void)
{
    db.commit();
    db.close();
}
//-----------------------------------------------------------------------------
void qt_appDataBase::db_write_item(const int row, const int col, qt_inventar_item &item)
{
    int          db_predmet_ref;
    int          db_predmet_count = item.get_predmet_count();
    PREDMET_TYPE db_predmet_type  = item.get_predmet_type();
    QString      db_predmet_image = item.get_predmet_img();
    QString      db_predmet_name  = item.get_predmet_name();

    QSqlQuery    query;
    QSqlRecord   inventar_rec;
    QSqlRecord   predmet_rec;

    QString str = QString::fromUtf8("SELECT predmetId FROM predmet WHERE type = %1 AND name = '%2';").arg((int)db_predmet_type).arg(db_predmet_name);
    if ( !query.exec(str) )
    {
        qDebug() << QString::fromUtf8("Не могу найти предмет в таблице predmet! ");
        qDebug() << QString::fromUtf8("Ошибка: ") << query.lastError().text();
        qDebug() << str;

        // throw some_err;
        return;
    }

    predmet_rec = query.record();
    query.next();
    db_predmet_ref  = query.value(predmet_rec.indexOf("predmetId")).toInt();

    str = QString::fromUtf8
          (
                "UPDATE inventar "
                "SET predmetRef = %1 "
                "WHERE row = %2 AND col = %3; "
          ).arg(db_predmet_ref).arg(row).arg(col);

    if (!query.exec(str))
    {
        qDebug() << QString::fromUtf8("Ошибка при изменении значения в таблице inventar!");
        qDebug() << QString::fromUtf8("Ошибка: ") << query.lastError().text();
        qDebug() << str;

        // throw some_err;
        return;
    }
    str = QString::fromUtf8
          (
                "UPDATE inventar "
                "SET count = %1 "
                "WHERE row = %2 AND col = %3; "
          ).arg(db_predmet_count).arg(row).arg(col);

    if (!query.exec(str))
    {
        qDebug() << QString::fromUtf8("Ошибка при изменении значения в таблице inventar!");
        qDebug() << QString::fromUtf8("Ошибка: ") << query.lastError().text();
        qDebug() << str;

        // throw some_err;
        return;
    }
}
//-----------------------------------------------------------------------------
qt_inventar_item* qt_appDataBase::db_read_item (const int row, const int col)
{
    int          fdb_predmet_ref;
    int          fdb_predmet_count;
    PREDMET_TYPE fdb_predmet_type;
    QString      fdb_predmet_image;
    QString      fdb_predmet_name;

    QSqlQuery    query;
    QSqlRecord   inventar_rec;
    QSqlRecord   predmet_rec;

    QString str = QString::fromUtf8("SELECT * FROM inventar WHERE row = %1 AND col = %2;").arg(row).arg(col);

    if ( !query.exec(str) )
    {
        qDebug() << QString::fromUtf8("Не могу считать данные из таблицы inventar! ");
        qDebug() << QString::fromUtf8("Ошибка: ") << query.lastError().text();
        qDebug() << str;

        // throw some_err;
        return NULL;
    }
    query.next();
    inventar_rec = query.record();
    fdb_predmet_ref   = query.value(inventar_rec.indexOf("predmetRef")).toInt();
    fdb_predmet_count = query.value(inventar_rec.indexOf("count")).toInt();

    str = QString::fromUtf8("SELECT * FROM predmet WHERE predmetId = %1;").arg(fdb_predmet_ref);

    if ( !query.exec(str) )
    {
        qDebug() << QString::fromUtf8("Не могу считать данные из таблицы predmet! ");
        qDebug() << QString::fromUtf8("Ошибка: ") << query.lastError().text();
        qDebug() << str;

        // throw some_err;
        return NULL;
    }

    predmet_rec = query.record();
    query.next();
    fdb_predmet_type  = (PREDMET_TYPE)query.value(predmet_rec.indexOf("type")).toInt();
    fdb_predmet_image = query.value(predmet_rec.indexOf("image")).toString();
    fdb_predmet_name  = query.value(predmet_rec.indexOf("name")).toString();

    qt_predmet* fdb_predmet = new qt_predmet;
    fdb_predmet->setFixedSize(100, 100);
    fdb_predmet->set_predmet_type(fdb_predmet_type);
    fdb_predmet->set_predmet_img(fdb_predmet_image);

    qt_inventar_item* item = new qt_inventar_item;
    item->setFixedSize(100, 100);
    item->set_predmet(*fdb_predmet);
    item->set_predmet_count(fdb_predmet_count);

    return item;
}
//-----------------------------------------------------------------------------
/*
CREATE TABLE addressbook (
number INTEGER PRIMARY KEY NOT NULL,
name VARCHAR(15),
phone VARCHAR(12),
email VARCHAR(15)
);

INSERT INTO addressbook (number, name, phone, email)
VALUES(1, 'Piggy', '+49 631322187', 'piggy@mega.de');

SELECT email
FROM addressbook
WHERE name = 'Piggy';

UPDATE addressbook
SET email = 'piggy@supermega.de'
WHERE name = 'Piggy';

DELETE FROM addressbook
WHERE name = 'Piggy';
*/
//-----------------------------------------------------------------------------
