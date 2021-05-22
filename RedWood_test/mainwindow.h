//-----------------------------------------------------------------------------
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//-----------------------------------------------------------------------------
#include <QMainWindow>
//-----------------------------------------------------------------------------
#include "qt_appdatabase.h"
#include "qt_inventar.h"
#include "qt_predmet.h"
//-----------------------------------------------------------------------------
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
//-----------------------------------------------------------------------------
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    qt_predmet     apple;
    qt_inventar    inventar;
    qt_appDataBase appDataBase;
};
//-----------------------------------------------------------------------------
#endif // MAINWINDOW_H
//-----------------------------------------------------------------------------
