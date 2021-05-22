//-----------------------------------------------------------------------------
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QImage>
//-----------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    qRegisterMetaType<PREDMET_TYPE>("PREDMET_TYPE");

    ui->setupUi(this);

    apple.set_predmet_type(GREEN_APPLE);
    apple.set_predmet_img(QString::fromUtf8("c:/green_apple.jpg"));

    QPainter painter(ui->widget_predmet);
    QImage   img(apple.get_predmet_img());
    painter.drawImage(0,0,img);
}
//-----------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}
//-----------------------------------------------------------------------------
