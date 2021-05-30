QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    qt_appdatabase.cpp \
    qt_inventar.cpp \
    qt_inventar_item.cpp \
    qt_inventar_itemmimedata.cpp \
    qt_predmet.cpp \
    qt_predmetmimedata.cpp

HEADERS += \
    mainwindow.h \
    qt_appdatabase.h \
    qt_inventar.h \
    qt_inventar_item.h \
    qt_inventar_itemmimedata.h \
    qt_predmet.h \
    qt_predmetmimedata.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    img/green-apple.jpg \
    img/red-apple.jpg

RESOURCES += \
    RedWood_test.qrc
