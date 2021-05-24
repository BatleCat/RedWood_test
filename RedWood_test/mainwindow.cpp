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
#include <QtDebug>
#include <QDataStream>
#include <QFile>
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

    qDebug() << QString::fromUtf8("Вывожу на экран Предмет.");

    apple.setFixedSize(ui->widget_predmet->width(), ui->widget_predmet->height());
    apple.set_predmet_type(GREEN_APPLE);
    apple.set_predmet_img(QString::fromUtf8(":/img/green-apple.jpg"));
    ui->widget_predmet->setLayout(apple.layout());

    qDebug() << QString::fromUtf8("Строю талицу Инвентаря.");

    ui->tableWidget_inventar->setColumnCount(3);

    ui->tableWidget_inventar->setRowCount(3);
    int i;
    for(i = 0; i < ui->tableWidget_inventar->rowCount(); i++)
    {
        ui->tableWidget_inventar->setRowHeight(i, 100);
    }
    for(i = 0; i < ui->tableWidget_inventar->columnCount(); i++)
    {
        ui->tableWidget_inventar->setColumnWidth(i, 100);
    }
    ui->tableWidget_inventar->resize(300 + ui->tableWidget_inventar->verticalHeader()->width(),
                                     300 + ui->tableWidget_inventar->horizontalHeader()->height()
                                     );
    ui->tableWidget_inventar->showGrid();
    {
        //-----------------------------------------------------------
        qt_inventar_item* inventar_item1 = new qt_inventar_item;
        inventar_item1->setFixedSize(100, 100);
        inventar_item1->set_predmet(apple);
        inventar_item1->set_predmet_count(5);
        //-----------------------------------------------------------
//        QFile file("1.bin");
//        {
//            file.open(QIODevice::Append);
//            QDataStream data(&file);

//            data << *inventar_item1;
//            file.flush();
//            file.close();
//        }
//        delete inventar_item1;
//        inventar_item1 = new qt_inventar_item;
//        inventar_item1->setFixedSize(100, 100);
//        {
//            file.open(QIODevice::ReadOnly);
//            QDataStream data(&file);

//            data >> *inventar_item1;
//            file.flush();
//            file.close();
//        }
        //-----------------------------------------------------------
        ui->tableWidget_inventar->setCellWidget(0, 0, inventar_item1);
        //-----------------------------------------------------------
        qt_inventar_item* inventar_item2 = new qt_inventar_item;
        inventar_item2->setFixedSize(100, 100);
        inventar_item2->set_predmet(apple);
        inventar_item2->set_predmet_count(20);
        ui->tableWidget_inventar->setCellWidget(0, 1, inventar_item2);
        //-----------------------------------------------------------
        qt_inventar_item* inventar_item3 = new qt_inventar_item;
        inventar_item3->setFixedSize(100, 100);
        inventar_item3->set_predmet(apple);
        inventar_item3->set_predmet_count(15);
        ui->tableWidget_inventar->setCellWidget(1, 1, inventar_item3);
        //-----------------------------------------------------------
        qt_inventar_item* inventar_item4 = new qt_inventar_item;
        inventar_item4->setFixedSize(100, 100);
        inventar_item4->set_predmet(apple);
        inventar_item4->set_predmet_count(3);
        ui->tableWidget_inventar->setCellWidget(1, 0, inventar_item4);
        inventar_item4->apend_one_predmet();
        inventar_item2->apend_one_predmet();
        inventar_item4->remove_one_predmet();
    }

}
//-----------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}
//-----------------------------------------------------------------------------
