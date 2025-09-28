QT       += core gui network charts sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    keyboard.cpp \
    main.cpp \
    mainwidget.cpp \
    socketclient.cpp \
    tab1socket.cpp \
    tab2sensor.cpp \
    tab3sqlite.cpp

HEADERS += \
    keyboard.h \
    mainwidget.h \
    socketclient.h \
    tab1socket.h \
    tab2sensor.h \
    tab3sqlite.h

FORMS += \
    keyboard.ui \
    mainwidget.ui \
    tab1socket.ui \
    tab2sensor.ui \
    tab3sqlite.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
