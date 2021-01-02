QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    pvz_widget.cpp \
    common.cpp \
    plants.cpp \
    zombies.cpp \
    store.cpp \
    map.cpp \
    bullets.cpp

HEADERS += \
    pvz_widget.h \
    common.h \
    plants.h \
    zombies.h \
    store.h \
    map.h \
    bullets.h

FORMS += \
    pvz_widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

QT += multimedia

RC_ICONS = icon.ico
