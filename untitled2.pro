#-------------------------------------------------
#
# Project created by QtCreator 2013-10-14T07:59:07
#
#-------------------------------------------------

QT       += core gui

TARGET = untitled2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    frameprocessor.cpp \
    videoprocessor.cpp \
    frameanalyzer.cpp \
    frameanalyzerhistogram.cpp \
    QRprocessor.cpp \
    QRanalyzer.cpp

HEADERS  += mainwindow.h \
    frameprocessor.h \
    videoprocessor.h \
    frameanalyzer.h \
    frameanalyzerhistogram.h \
    QRprocessor.h \
    QRanalyzer.h

FORMS    += mainwindow.ui

#------------------------------QRcode-------------------------------------------------------------
unix:!macx:!symbian: LIBS += -lqrencode

#------------------------------R------------------------------------------------------------------
unix:!macx:!symbian: LIBS += -L$$PWD/../../../usr/local/lib/R/site-library/RInside/lib/ -lRInside

INCLUDEPATH += /usr/local/lib/R/site-library/RInside/include
DEPENDPATH += /usr/local/lib/R/site-library/RInside

unix:!macx:!symbian: LIBS += -L$$PWD/../../../usr/local/lib/R/site-library/Rcpp/lib/ -lRcpp

INCLUDEPATH += /usr/local/lib/R/site-library/Rcpp/lib/include
DEPENDPATH += /usr/local/lib/R/site-library/Rcpp/lib

unix:!macx:!symbian: LIBS += -L$$PWD/../../../usr/lib/ -lR

INCLUDEPATH += /usr/lib/include
DEPENDPATH += /usr/lib

unix:!macx:!symbian: LIBS += -L$$PWD/../../../usr/lib/ -lR

INCLUDEPATH += $$PWD/../../../usr/share/R/include
DEPENDPATH += $$PWD/../../../usr/share/R/include

#------------------------------openCV------------------------------------------------------------
unix:!macx:!symbian: LIBS += -L$$PWD/../../../usr/local/lib/ -lopencv_core

INCLUDEPATH += $$PWD/../../../usr/local/include/opencv
DEPENDPATH += $$PWD/../../../usr/local/include/opencv

unix:!macx:!symbian: LIBS += -L$$PWD/../../../usr/local/lib/ -lopencv_highgui

INCLUDEPATH += $$PWD/../../../usr/local/include/opencv
DEPENDPATH += $$PWD/../../../usr/local/include/opencv

unix:!macx:!symbian: LIBS += -L$$PWD/../../../usr/local/lib/ -lopencv_imgproc
INCLUDEPATH += $$PWD/../../../usr/local/include/opencv
DEPENDPATH += $$PWD/../../../usr/local/include/opencv

#----------------------mylibraries----------------------------------------------------------------
unix:!macx:!symbian: LIBS += -L$$PWD/../../../usr/lib/ -lVideo

INCLUDEPATH += $$PWD/../../../usr/include
DEPENDPATH += $$PWD/../../../usr/include



#unix:!macx:!symbian: LIBS += -L$$PWD/ -lvideoprocessing2

#INCLUDEPATH += $$PWD/
#DEPENDPATH += $$PWD/

