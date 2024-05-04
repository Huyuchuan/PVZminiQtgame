#-------------------------------------------------
#
# Project created by QtCreator 2021-05-09T10:46:16
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ../PlantsVsZombies
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

CONFIG += c++11

SOURCES += \
    src/simpleQtLogger.cpp \
    src/other/button.cpp \
    src/other/card.cpp \
    src/other/map.cpp \
    src/other/mower.cpp \
    src/other/other.cpp \
    src/other/pea.cpp \
    src/other/shop.cpp \
    src/other/shovel.cpp \
    src/other/sun.cpp \
    src/other/main.cpp \
    src/other/mainwindow.cpp \
    src/plant/cherrybomb.cpp \
    src/plant/peashooter.cpp \
    src/plant/plant.cpp \
    src/plant/potatomine.cpp \
    src/plant/repeater.cpp \
    src/plant/snowpea.cpp \
    src/plant/sunflower.cpp \
    src/plant/wallnut.cpp \
    src/zombie/basiczombie.cpp \
    src/zombie/bucketzombie.cpp \
    src/zombie/conezombie.cpp \
    src/zombie/footballzombie.cpp \
    src/zombie/screenzombie.cpp \
    src/zombie/zombie.cpp

HEADERS += \
    src/simpleQtLogger.h \
    src/other/button.h \
    src/other/card.h \
    src/other/map.h \
    src/other/mower.h \
    src/other/other.h \
    src/other/pea.h \
    src/other/shop.h \
    src/other/shovel.h \
    src/other/sun.h \
    src/other/mainwindow.h \
    src/plant/cherrybomb.h \
    src/plant/peashooter.h \
    src/plant/plant.h \
    src/plant/potatomine.h \
    src/plant/repeater.h \
    src/plant/snowpea.h \
    src/plant/sunflower.h \
    src/plant/wallnut.h \
    src/zombie/basiczombie.h \
    src/zombie/bucketzombie.h \
    src/zombie/conezombie.h \
    src/zombie/footballzombie.h \
    src/zombie/screenzombie.h \
    src/zombie/zombie.h \
    src/other/init.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc


# 图标
RC_ICONS += \
    ./images/window.ico
