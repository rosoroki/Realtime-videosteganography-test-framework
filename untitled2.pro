#-------------------------------------------------
#
# Project created by QtCreator 2013-10-14T07:59:07
#
# SOROKIN ROMAN, 2013
#-------------------------------------------------

QT       += core gui

TARGET = videostegotool
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    frameprocessor.cpp \
    videoprocessor.cpp \
    frameanalyzer.cpp \
    frameanalyzerhistogram.cpp \
    QRprocessor.cpp \
    losses.cpp \
    distortion.cpp \
    qualityreduction.cpp \
    basicdistortion.cpp \
    basicqualityreduction.cpp \
    comparativeanalyzer.cpp \
    blindanalyzer.cpp

HEADERS  += mainwindow.h \
    frameprocessor.h \
    videoprocessor.h \
    frameanalyzer.h \
    frameanalyzerhistogram.h \
    QRprocessor.h \
    losses.h \
    distortion.h \
    qualityreduction.h \
    basicdistortion.h \
    basicqualityreduction.h \
    comparativeanalyzer.h \
    blindanalyzer.h

FORMS    += mainwindow.ui

#------------------------------QRcode-------------------------------------------------------------
unix:!macx:!symbian: LIBS += -lqrencode

#------------------------------openCV------------------------------------------------------------
unix:!macx:!symbian: LIBS += -lopencv_core

unix:!macx:!symbian: LIBS += -lopencv_highgui

unix:!macx:!symbian: LIBS += -lopencv_imgproc

OTHER_FILES += \
    INSTALL \
    BUILD.sh \
    TotalInstallScript.sh
