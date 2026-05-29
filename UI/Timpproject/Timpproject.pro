QT += core gui widgets network sql printsupport charts

CONFIG += c++17

QMAKE_CXXFLAGS += -Wa,-mbig-obj
QMAKE_CFLAGS += -Wa,-mbig-obj

INCLUDEPATH += $$PWD

SOURCES += \
    aboutwindow.cpp \
    databasemanager.cpp \
    emailsender.cpp \
    forgotpassword.cpp \
    graphwindow.cpp \
    logintimp.cpp \
    main.cpp \
    maintimp.cpp \
    qcustomplot.cpp \
    registerwindow.cpp \
    servicemanager.cpp \
    welcomewindow.cpp

HEADERS += \
    aboutwindow.h \
    databasemanager.h \
    emailsender.h \
    forgotpassword.h \
    graphwindow.h \
    logintimp.h \
    maintimp.h \
    qcustomplot.h \
    registerwindow.h \
    servicemanager.h \
    welcomewindow.h

FORMS += \
    aboutwindow.ui \
    forgotpassword.ui \
    graphwindow.ui \
    logintimp.ui \
    maintimp.ui \
    registerwindow.ui \
    welcomewindow.ui

RESOURCES += \
    images.qrc

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
