QT += testlib network sql
QT -= gui
CONFIG += console c++17
CONFIG -= app_bundle
TEMPLATE = app

INCLUDEPATH += ../002TCPserver/TCPserver
INCLUDEPATH += ../002Timpproject/Timpproject

SOURCES += \
    tst_alltests.cpp \
    ../002TCPserver/TCPserver/controller.cpp \
    ../002TCPserver/TCPserver/serverdb.cpp \
    ../002TCPserver/TCPserver/emailservice.cpp \
    ../002Timpproject/Timpproject/graphwindow.cpp

HEADERS += \
    ../002TCPserver/TCPserver/controller.h \
    ../002TCPserver/TCPserver/serverdb.h \
    ../002TCPserver/TCPserver/emailservice.h \
    ../002Timpproject/Timpproject/graphwindow.h
