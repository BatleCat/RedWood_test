//-----------------------------------------------------------------------------
#include "mainwindow.h"
#include "ui_mainwindow.h"
//-----------------------------------------------------------------------------
#include <QCoreApplication>
#include <QPainter>
#include <QImage>
#include <QHBoxLayout>
#include <QLabel>
#include <QColor>
#include <QDataStream>
#include <QFile>
//-----------------------------------------------------------------------------
#include <QtDebug>
#include <QtSql>
#include <QStringList>
#include <QList>
#include <QVariant>
//-----------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    qRegisterMetaType<PREDMET_TYPE>("PREDMET_TYPE");

    ui->setupUi(this);

//    QCoreApplication::setOrganizationName(QString::fromUtf8("Company Name"));
    QCoreApplication::setApplicationName(QString::fromUtf8("RedWood_test"));
    QCoreApplication::setApplicationVersion(QString::fromUtf8("0.0.0.1"));

//    setWindowIcon(QIcon(":/images/icon_file.ico"));
    setWindowTitle(QString::fromUtf8("RedWood test"));

//    qDebug() << QString::fromUtf8("Вывожу на экран Предмет.");

    apple.setFixedSize(ui->widget_predmet->width(), ui->widget_predmet->height());
    apple.set_predmet_type(GREEN_APPLE);
    apple.set_predmet_img(QString::fromUtf8(":/img/green-apple.jpg"));
    QHBoxLayout *qhbl = new QHBoxLayout(ui->widget_predmet);
    qhbl->addWidget(&apple);

//    qDebug() << QString::fromUtf8("Строю талицу Инвентаря.");

//    ui->tableWidget_inventar->setColumnCount(3);

//    ui->tableWidget_inventar->setRowCount(3);
//    int i;
//    for(i = 0; i < ui->tableWidget_inventar->rowCount(); i++)
//    {
//        ui->tableWidget_inventar->setRowHeight(i, 100);
//    }
//    for(i = 0; i < ui->tableWidget_inventar->columnCount(); i++)
//    {
//        ui->tableWidget_inventar->setColumnWidth(i, 100);
//    }
//    ui->tableWidget_inventar->resize(300 + ui->tableWidget_inventar->verticalHeader()->width(),
//                                     300 + ui->tableWidget_inventar->horizontalHeader()->height()
//                                     );
    ui->tableWidget_inventar->showGrid();

    int col;
    int row;
    for (col = 0; col < ui->tableWidget_inventar->columnCount(); col++)
    {
        int w = 100;
        for (row = 0; row < ui->tableWidget_inventar->rowCount(); row++)
        {
            //-----------------------------------------------------------
            int h = 100;
            qt_inventar_item* inventar_item = new qt_inventar_item;
            inventar_item->setFixedSize(w, h);
            ui->tableWidget_inventar->setCellWidget(row, col, inventar_item);
            //-----------------------------------------------------------
        }
    }
    //------------------------------------------------------------------------
    qDebug() << QString::fromUtf8("Начинаю работать с базой данных");
    //------------------------------------------------------------------------
    // Create connections
    //------------------------------------------------------------------------
    qDebug() << QString::fromUtf8("Создаю базу данных");

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("redwoodtest.sqlite");
    db.setHostName("localhost");
//    db.setUserName("user");
//    db.setPassword("");
    if (!db.open())
    {
        qDebug() << QString::fromUtf8("Cannot open database:") << db.lastError().text();
    }
    else
    {
        qDebug() << QString::fromUtf8("Open database succesful");
    }

    QStringList lst = db.tables();
    foreach (QString str, lst)
    {
        qDebug() << "Table:" << str;
    }

    //------------------------------------------------------------------------
    //------------------------------------------------------------------------
    QSqlQuery  query;
    QSqlRecord rec;
    QSqlError  db_err;
    {
        if (!query.exec("PRAGMA foreign_keys = ON;"))
        {
            qDebug() << "Unable to foreign_keys = ON : " << db.lastError().text();
        }

        query.exec("PRAGMA foreign_keys;");
        QList<QVariant> lst = query.boundValues().values();
        foreach (QVariant x, lst)
        {
            qDebug() << "PRAGMA foreign_keys = " << x.toString().toUtf8().data();
        }

//        db_err = query.lastError();
//        qDebug() << db_err.text();
    }
    //------------------------------------------------------------------------
    // Создаем таблицу Предметы
    //-------------------------------------------------------------------------
    qDebug() << QString::fromUtf8("Создаю таблицу Предметы");
    QString str = QString::fromUtf8(
        "CREATE TABLE predmet ( "
        "predmetId INTEGER PRIMARY KEY NOT NULL, "
        "type      INTEGER UNIQUE NOT NULL, "
        "image     TEXT, "
        "name      TEXT NOT NULL "
        ");"
    );
    if (!query.exec(str))
    {
        qDebug() << "Unable to create a table: " << db.lastError().text();
    }
    //-------------------------------------------------------------------------
    // Создаю таблицу Инвентарь
    //-------------------------------------------------------------------------
    qDebug() << QString::fromUtf8("Создаю таблицу Инвентарь");
    str = QString::fromUtf8(
        "CREATE TABLE inventar ( "
        "inventarId INTEGER PRIMARY KEY NOT NULL, "
        "row        INTEGER NOT NULL, "
        "col        INTEGER NOT NULL, "
        "predmetRef INTEGER NOT NULL, "
        "count      INTEGER NOT NULL, "
        "FOREIGN KEY(predmetRef) REFERENCES predmet(predmetId) "
        ");"
    );
    if (!query.exec(str))
    {
        qDebug() << "Unable to create a table: " << db.lastError().text();
        query.next();
        qDebug() << "Unable to create a table: " << db.lastError().text();
    }
    //-------------------------------------------------------------------------
    // Добавляем данные в базу
    //-------------------------------------------------------------------------
    QString strF = QString::fromUtf8(
        "INSERT INTO predmet (predmetId, type, image, name) "
        "VALUES(%1, '%2', '%3', '%4');"
    );

    str =   strF.arg("1")
                .arg(int(PREDMET_TYPE::UNKNOW_PREDMET))
                .arg(QString::fromUtf8(":/img/"))
                .arg(QString::fromUtf8("Неизвестный"));
    if (!query.exec(str))
    {
        qDebug() << "Unable to make insert operation";
    }

    str =   strF.arg("2")
                .arg(int(PREDMET_TYPE::GREEN_APPLE))
                .arg(QString::fromUtf8(":/img/green-apple.jpg"))
                .arg(QString::fromUtf8("Зеленое яблоко"));
    if (!query.exec(str))
    {
        qDebug() << "Unable to make insert operation";
    }

    str =   strF.arg("3")
                .arg(int(PREDMET_TYPE::RED_APPLE))
                .arg(QString::fromUtf8(":/img/red-apple.jpg"))
                .arg(QString::fromUtf8("Красное яблоко"));
    if (!query.exec(str))
    {
        qDebug() << "Unable to make insert operation";
    }

    //-------------------------------------------------------------------------
    // Считываем данные из базы
    //-------------------------------------------------------------------------
    if (!query.exec("SELECT * FROM predmet;"))
    {
        qDebug() << "Unable to execute query — exiting";
    }

    rec = query.record();
    int nNumber = 0;
    PREDMET_TYPE fdb_type;
    QString      fdb_image;
    QString      fdb_name;

    while (query.next())
    {
        nNumber   = query.value(rec.indexOf("predmetId")).toInt();
        fdb_type  = (PREDMET_TYPE)query.value(rec.indexOf("type")).toInt();
        fdb_image = query.value(rec.indexOf("image")).toString();
        fdb_name  = query.value(rec.indexOf("name")).toString();

        qDebug() << nNumber
                 << " | " << fdb_type
                 << " | " << fdb_image
                 << " | " << fdb_name;
    }
    //-------------------------------------------------------------------------
    // Добавляем данные в таблицу Инвентарь
    //-------------------------------------------------------------------------
    qDebug() << QString::fromUtf8("Заполняю таблицу Инвентарь");
    strF = QString::fromUtf8(
        "INSERT INTO inventar (inventarId, row, col, predmetRef, count) "
        "VALUES(%1, '%2', '%3', '%4', '%5');"
    );
    row = 0;
    col = 0;
    int count = 0;
    for (col = 0; col < ui->tableWidget_inventar->columnCount(); col++)
    {
        for (row = 0; row < ui->tableWidget_inventar->rowCount(); row++)
        {
            count++;
            str =   strF.arg(count)
                        .arg(row)
                        .arg(col)
                        .arg(1)
                        .arg(0);

            if (!query.exec(str))
            {
                qDebug() << "Unable to make insert operation";
                qDebug() << str;
            }
        }
    }
    qDebug() << QString::fromUtf8("Таблица ""Инвентарь"" заполнена");
    //-------------------------------------------------------------------------
    //-------------------------------------------------------------------------
    str = QString::fromUtf8("SELECT predmetId FROM predmet WHERE name = ") + QString::fromUtf8("'Зеленое яблоко';");
    query.exec(str);
    qDebug() << query.lastError().text();
    query.next();
    rec = query.record();
    int refId = query.value(rec.indexOf("predmetId")).toInt();
    qDebug() << refId;
    //-------------------------------------------------------------------------

    qDebug() << QString::fromUtf8("Изменяю значение PredmetRef и count для элементов с row=1 col=2");
    str = QString::fromUtf8("UPDATE inventar "
        "SET predmetRef = %1 "
        "WHERE row = 1 AND col = 2; "
            ).arg(refId);
    if (!query.exec(str))
    {
        db_err = query.lastError();
        qDebug() << QString::fromUtf8("Ошибка при изменении значения!");
//        qDebug() << db_err.databaseText();
//        qDebug() << db_err.driverText();
        qDebug() << db_err.text();
    }
    str = QString::fromUtf8("UPDATE inventar "
        "SET count = 5 "
        "WHERE row = 1 AND col = 2; "
            );
    if (!query.exec(str))
    {
        db_err = query.lastError();
        qDebug() << QString::fromUtf8("Ошибка при изменении значения!");
//        qDebug() << db_err.databaseText();
//        qDebug() << db_err.driverText();
        qDebug() << db_err.text();
    }
    //-------------------------------------------------------------------------
    str = "SELECT inventarId FROM inventar WHERE row = 1 AND col = 2;";
    query.exec(str);
    db_err = query.lastError();
    rec = query.record();
    query.next();
    qDebug() << query.value(rec.indexOf("inventarId")).toInt();
    qDebug() << db_err.text();
    //-------------------------------------------------------------------------
    // Считываем данные из базы
    //-------------------------------------------------------------------------
    qDebug() << QString::fromUtf8("Считываю содержимое таблицы ""Инвентарь"" ");
    if (!query.exec("SELECT * FROM inventar;"))
    {
        qDebug() << "Unable to execute query — exiting";
    }

    rec = query.record();
    nNumber = 0;
    row = 0;
    col = 0;
    int predmet_ref = 0;
    count = 0;

    while (query.next())
    {
        nNumber     = query.value(rec.indexOf("inventarId")).toInt();
        row         = query.value(rec.indexOf("row")).toInt();
        col         = query.value(rec.indexOf("col")).toInt();
        predmet_ref = query.value(rec.indexOf("predmetRef")).toInt();
        count       = query.value(rec.indexOf("count")).toInt();

        qDebug() << nNumber
                 << " | " << row
                 << " | " << col
                 << " | " << predmet_ref
                 << " | " << count;
    }
    db.close();
    //-------------------------------------------------------------------------
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
}
//-----------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}
//-----------------------------------------------------------------------------
