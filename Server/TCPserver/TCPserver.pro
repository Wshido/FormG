QT -= gui
QT += core network sql

CONFIG += c++17 console
CONFIG -= app_bundle

win32 {
    LIBS += -L"C:/Program Files/PostgreSQL/16/lib" -llibpq
    INCLUDEPATH += "C:/Program Files/PostgreSQL/16/include"
} else {
    LIBS += -lpq
}

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
