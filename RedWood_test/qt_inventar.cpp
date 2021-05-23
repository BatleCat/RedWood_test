//-----------------------------------------------------------------------------
#include "qt_inventar.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QImage>
//-----------------------------------------------------------------------------
qt_inventar::qt_inventar(QObject *parent) : QObject(parent)
{

}
//-----------------------------------------------------------------------------
/*
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
*/
