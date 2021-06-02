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
#include "qt_inventar_item.h"
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

    //-------------------------------------------------------------------------
    // Вывожу на экран Предмет
    //-------------------------------------------------------------------------
    apple.setFixedSize(ui->widget_predmet->width(), ui->widget_predmet->height());
    apple.set_predmet_type(GREEN_APPLE);
    apple.set_predmet_img(QString::fromUtf8(":/img/green-apple.jpg"));
    QHBoxLayout *qhbl = new QHBoxLayout(ui->widget_predmet);
    qhbl->addWidget(&apple);
    //-------------------------------------------------------------------------
    ui->widget_gameField->setVisible(false);
    ui->widget_mainMenu->setVisible(true);
    //-------------------------------------------------------------------------
    connect( ui->pushButton_newGame,  SIGNAL( pressed() ), this, SLOT( startGame() ) );
    connect( ui->pushButton_mainMenu, SIGNAL( pressed() ), this, SLOT( mainMenu()  ) );
    //-------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}
//-----------------------------------------------------------------------------
void MainWindow::startGame(void)
{
    //-------------------------------------------------------------------------
    ui->widget_gameField->setVisible(true);
    ui->widget_mainMenu->setVisible(false);
    //-------------------------------------------------------------------------
    ui->tableWidget_inventar->showGrid();
    //-------------------------------------------------------------------------
    int col;
    int row;
    for (col = 0; col < ui->tableWidget_inventar->columnCount(); col++)
    {
        int w = 100;
        for (row = 0; row < ui->tableWidget_inventar->rowCount(); row++)
        {
            //-----------------------------------------------------------
            int h = 100;
            qt_inventar_item* inventar_item = appDataBase.db_read_item(row, col);
            inventar_item->setFixedSize(w, h);
            ui->tableWidget_inventar->setCellWidget(row, col, inventar_item);
            //-----------------------------------------------------------
        }
    }
    //-------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------
void MainWindow::mainMenu(void)
{
    //-------------------------------------------------------------------------
    ui->widget_gameField->setVisible(false);
    ui->widget_mainMenu->setVisible(true);
    //-------------------------------------------------------------------------
    int col;
    int row;
    for (col = 0; col < ui->tableWidget_inventar->columnCount(); col++)
    {
        for (row = 0; row < ui->tableWidget_inventar->rowCount(); row++)
        {
            //-----------------------------------------------------------
            qt_inventar_item* inventar_item = (qt_inventar_item*) ui->tableWidget_inventar->cellWidget(row, col);
            appDataBase.db_write_item(row, col, *inventar_item);
            //-----------------------------------------------------------
        }
    }
    //-------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------
