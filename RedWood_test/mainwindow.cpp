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
    QHBoxLayout *qhbl = new QHBoxLayout(ui->widget_predmet);
    qhbl->addWidget(&apple);
    //ui->widget_predmet->setLayout(apple.layout());

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

    int col;
    int row;
    for (col = 0; col < ui->tableWidget_inventar->columnCount(); col++)
        for (row = 0; row < ui->tableWidget_inventar->rowCount(); row++)
        {
            //-----------------------------------------------------------
            qt_inventar_item* inventar_item = new qt_inventar_item;
            inventar_item->setFixedSize(100, 100);
            ui->tableWidget_inventar->setCellWidget(row, col, inventar_item);
            //-----------------------------------------------------------
        }

}
//-----------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}
//-----------------------------------------------------------------------------
