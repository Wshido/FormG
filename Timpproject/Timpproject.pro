QT += widgets printsupport
QT += charts network widgets
QT += core gui widgets network
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
QMAKE_CXXFLAGS += -Wa,-mbig-obj
QMAKE_CFLAGS   += -Wa,-mbig-obj
SOURCES += \
    aboutwindow.cpp \
    forgotpassword.cpp \
    graphwindow.cpp \
    logintimp.cpp \
    main.cpp \
    maintimp.cpp \
    qcustomplot.cpp \
    registerwindow.cpp \
    welcomewindow.cpp

HEADERS += \
    aboutwindow.h \
    forgotpassword.h \
    graphwindow.h \
    logintimp.h \
    maintimp.h \
    qcustomplot.h \
    registerwindow.h \
    welcomewindow.h

FORMS += \
    aboutwindow.ui \
    forgotpassword.ui \
    graphwindow.ui \
    logintimp.ui \
    maintimp.ui \
    registerwindow.ui \
    welcomewindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD

RESOURCES += \
    images.qrc
