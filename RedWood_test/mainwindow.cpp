//-----------------------------------------------------------------------------
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QImage>
#include <QHBoxLayout>
#include <QLabel>
#include <QColor>
#include <QtDebug>
//-----------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    qRegisterMetaType<PREDMET_TYPE>("PREDMET_TYPE");

    ui->setupUi(this);

    apple.set_predmet_type(GREEN_APPLE);
    apple.set_predmet_img(QString::fromUtf8(":/img/green-apple.jpg"));

    QImage   img;
//    if ( !img.load( apple.get_predmet_img() ) )
//    {
//        qDebug() << "Error load JPG-file!";
//    }
    img.load(apple.get_predmet_img(), "JPG");

    {
        QImage img1 = img.scaled( ui->widget_predmet->size(), Qt::KeepAspectRatio );

        QHBoxLayout* phbx = new QHBoxLayout;
        phbx->setMargin(0);
        phbx->setSpacing(0);

        QLabel* plbl = new QLabel;
        plbl->setFixedSize(img1.size());
        plbl->setPixmap(QPixmap::fromImage(img1));

//      QPixmap pix_map(apple.get_predmet_img());
//      plbl->setFixedSize(pix_map.size());
//      plbl->setPixmap(pix_map);

        phbx->addWidget(plbl);
//      ui->widget_predmet->setFixedSize(img.size());
        ui->widget_predmet->setLayout(phbx);
    }

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
        QLabel*      plbl;
        QWidget*     cell_widget;
        QVBoxLayout* pvbx;

        QImage img1 = img.scaled( 100, 100, Qt::KeepAspectRatio );
        //-----------------------------------------------------------
        pvbx = new QVBoxLayout;
        pvbx->setMargin(0);
        pvbx->setSpacing(0);

        plbl = new QLabel;
        plbl->setFixedSize(img1.size());
        plbl->setPixmap(QPixmap::fromImage(img1));

        pvbx->addWidget(plbl);

        plbl = new QLabel;
        plbl->setAlignment(Qt::AlignRight | Qt::AlignBottom);
        plbl->setNum(2);

        pvbx->addWidget(plbl);

        cell_widget = new QWidget;
        cell_widget->setLayout(pvbx);

        ui->tableWidget_inventar->setCellWidget(0, 1, cell_widget);
        //-----------------------------------------------------------
        pvbx = new QVBoxLayout;
        pvbx->setMargin(0);
        pvbx->setSpacing(0);

        plbl = new QLabel;
        plbl->setFixedSize(img1.size());
        plbl->setPixmap(QPixmap::fromImage(img1));

        pvbx->addWidget(plbl);

        plbl = new QLabel;
        plbl->setAlignment(Qt::AlignRight | Qt::AlignBottom);
        plbl->setNum(20);

        pvbx->addWidget(plbl);

        cell_widget = new QWidget;
        cell_widget->setLayout(pvbx);

        ui->tableWidget_inventar->setCellWidget(1, 1, cell_widget);
        //-----------------------------------------------------------
        pvbx = new QVBoxLayout;
        pvbx->setMargin(0);
        pvbx->setSpacing(0);

        plbl = new QLabel;
        plbl->setFixedSize(img1.size());
        plbl->setPixmap(QPixmap::fromImage(img1));

        pvbx->addWidget(plbl);

        plbl = new QLabel;
        plbl->setAlignment(Qt::AlignRight | Qt::AlignBottom);
        plbl->setNum(5);

        pvbx->addWidget(plbl);

        cell_widget = new QWidget;
        cell_widget->setLayout(pvbx);

        ui->tableWidget_inventar->setCellWidget(0, 0, cell_widget);
        //-----------------------------------------------------------
        qt_inventar_item* inventar_item = new qt_inventar_item;
        ui->tableWidget_inventar->setCellWidget(1, 0, inventar_item);
        inventar_item->apend_one_predmet();
//        inventar_item->apend_one_predmet();
        inventar_item->remove_one_predmet();
    }

}
//-----------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}
//-----------------------------------------------------------------------------
