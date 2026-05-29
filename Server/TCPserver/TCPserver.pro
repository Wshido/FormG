QT -= gui
QT += core network sql

CONFIG += c++17 console
CONFIG -= app_bundle

LIBS += -L"C:/Program Files/PostgreSQL/16/lib" -llibpq
INCLUDEPATH += "C:/Program Files/PostgreSQL/16/include"

SOURCES += \
    main.cpp \
    tcpserver.cpp \
    controller.cpp \
    serverdb.cpp \
    emailservice.cpp

HEADERS += \
    tcpserver.h \
    controller.h \
    serverdb.h \
    emailservice.h
