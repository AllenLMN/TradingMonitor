#-------------------------------------------------
#
# Project created by QtCreator 2019-05-22T11:35:04
#
#-------------------------------------------------


#include($$PWD/nzmqt.pri)
QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TradingMonitor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    qcustomplot.cpp \
    sent.cpp \
    mytracer.cpp \
    SnapshotReceive.cpp \
    orderreceive.cpp \
    set.cpp

HEADERS += \
        mainwindow.h \
    market_snapshot.h \
    define.h \
    qcustomplot.h \
    sent.h \
    market_snapshot.h \
    mytracer.h \
    order.h \
    order_action.h \
    order_side.h \
    order_status.h \
    offset.h \
    orderreceive.h \
    snapshotreceive.h \
    set.h

FORMS += \
        mainwindow.ui \
    set.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/./ -llibzmq
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/./ -llibzmqd

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
