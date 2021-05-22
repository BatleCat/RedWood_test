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

    QImage img1 = img.scaled( ui->widget_predmet->size(), Qt::KeepAspectRatio );

    QHBoxLayout* phbx = new QHBoxLayout;
    phbx->setMargin(0);
    phbx->setSpacing(0);

    QLabel* plbl = new QLabel;
    plbl->setFixedSize(img1.size());
    plbl->setPixmap(QPixmap::fromImage(img1));

//    QPixmap pix_map(apple.get_predmet_img());
//    plbl->setFixedSize(pix_map.size());
//    plbl->setPixmap(pix_map);

    phbx->addWidget(plbl);
//    ui->widget_predmet->setFixedSize(img.size());
    ui->widget_predmet->setLayout(phbx);
}
//-----------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}
//-----------------------------------------------------------------------------
